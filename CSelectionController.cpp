#include "CSelectionController.h"

CSelectionController::CSelectionController(CShapeController& shapeController)
	: m_shapeController(shapeController)
{
}

void CSelectionController::HandleEvent(const sf::Event& event)
{
	if (auto* mp = event.getIf<sf::Event::MouseButtonPressed>())
	{
		HandleMouseButtonPressed(*mp);
	}
	else if (auto* mm = event.getIf<sf::Event::MouseMoved>())
	{
		HandleMouseMoved(*mm);
	}
	else if (auto* mr = event.getIf<sf::Event::MouseButtonReleased>())
	{
		HandleMouseButtonReleased(*mr);
	}
	else if (auto* kp = event.getIf<sf::Event::KeyPressed>())
	{
		HandleKeyPressed(*kp);
	}
}

void CSelectionController::HandleMouseButtonPressed(const sf::Event::MouseButtonPressed& mp)
{
	if (mp.button != sf::Mouse::Button::Left)
	{
		return;
	}

	sf::Vector2f pos(static_cast<float>(mp.position.x), static_cast<float>(mp.position.y));
	bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);

	SelectShapeAt(CPoint(pos.x, pos.y), shift);

	if (!m_selectedShapes.empty())
	{
		m_isDragging = true;
		m_lastMousePos = pos;
	}
}

void CSelectionController::HandleMouseMoved(const sf::Event::MouseMoved& mm)
{
	if (!m_isDragging)
	{
		return;
	}

	sf::Vector2f pos(static_cast<float>(mm.position.x), static_cast<float>(mm.position.y));
	float dx = pos.x - m_lastMousePos.x;
	float dy = pos.y - m_lastMousePos.y;

	DragSelected(dx, dy);
	m_lastMousePos = pos;
}

void CSelectionController::HandleMouseButtonReleased(const sf::Event::MouseButtonReleased& mr)
{
	if (mr.button == sf::Mouse::Button::Left)
		m_isDragging = false;
}

void CSelectionController::HandleKeyPressed(const sf::Event::KeyPressed& kp)
{
	bool ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);

	if (ctrl && kp.code == sf::Keyboard::Key::G)
		GroupSelected();

	if (ctrl && kp.code == sf::Keyboard::Key::U)
		UngroupSelected();
}

void CSelectionController::DrawSelection(ICanvas& canvas) const
{
	for (const IShape* shape : m_selectedShapes)
	{
		const CRectD bounds = shape->GetBounds();
		const CPoint topLeft(bounds.left, bounds.top);
		const CPoint bottomRight(bounds.right, bounds.bottom);

		canvas.DrawRect(topLeft, bottomRight, SELECTION_FRAME_COLOR, 1.0);

		canvas.FillRect(CPoint(bounds.left - MARKER_HALF, bounds.top - MARKER_HALF),
			CPoint(bounds.left + MARKER_HALF, bounds.top + MARKER_HALF),
			SELECTION_MARKER_COLOR);
		canvas.FillRect(CPoint(bounds.right - MARKER_HALF, bounds.top - MARKER_HALF),
			CPoint(bounds.right + MARKER_HALF, bounds.top + MARKER_HALF),
			SELECTION_MARKER_COLOR);
		canvas.FillRect(CPoint(bounds.left - MARKER_HALF, bounds.bottom - MARKER_HALF),
			CPoint(bounds.left + MARKER_HALF, bounds.bottom + MARKER_HALF),
			SELECTION_MARKER_COLOR);
		canvas.FillRect(CPoint(bounds.right - MARKER_HALF, bounds.bottom - MARKER_HALF),
			CPoint(bounds.right + MARKER_HALF, bounds.bottom + MARKER_HALF),
			SELECTION_MARKER_COLOR);
	}
}

IShape* CSelectionController::FindTopmostShapeAt(CPoint point) const
{
	const auto& shapes = m_shapeController.GetShapes();
	for (auto it = shapes.rbegin(); it != shapes.rend(); ++it)
	{
		if ((*it)->ContainsPoint(point))
		{
			return it->get();
		}
	}
	return nullptr;
}

void CSelectionController::SelectShapeAt(CPoint point, bool shiftPressed)
{
	IShape* hit = FindTopmostShapeAt(point);

	if (!shiftPressed)
	{
		m_selectedShapes.clear();
	}

	if (hit == nullptr)
	{
		return;
	}

	auto it = std::find(m_selectedShapes.begin(), m_selectedShapes.end(), hit);
	if (shiftPressed && it != m_selectedShapes.end())
	{
		m_selectedShapes.erase(it);
	}
	else if (it == m_selectedShapes.end())
	{
		m_selectedShapes.push_back(hit);
	}
}

void CSelectionController::ClearSelection()
{
	m_selectedShapes.clear();
}

void CSelectionController::GroupSelected()
{
	if (m_selectedShapes.size() < MIN_SHAPES_FOR_GROUP)
	{
		return;
	}

	auto composite = std::make_unique<CCompositeShape>();

	auto& shapes = m_shapeController.GetShapes();
	for (auto it = shapes.begin(); it != shapes.end();)
	{
		auto* raw = it->get();
		if (std::find(m_selectedShapes.begin(), m_selectedShapes.end(), raw) != m_selectedShapes.end())
		{
			composite->Add(std::move(*it));
			it = shapes.erase(it);
		}
		else
		{
			++it;
		}
	}

	shapes.push_back(std::move(composite));

	m_selectedShapes.clear();
	m_selectedShapes.push_back(shapes.back().get());
}

void CSelectionController::UngroupSelected()
{
	if (m_selectedShapes.size() != SINGLE_SELECTED_SHAPE)
	{
		return;
	}

	auto* selected = m_selectedShapes.front();
	auto* composite = dynamic_cast<CCompositeShape*>(selected);
	if (composite == nullptr)
	{
		return;
	}

	auto children = composite->ReleaseChildren();

	auto& shapes = m_shapeController.GetShapes();
	for (auto it = shapes.begin(); it != shapes.end(); ++it)
	{
		if (it->get() == composite)
		{
			it = shapes.erase(it);
			break;
		}
	}

	for (auto& child : children)
	{
		shapes.push_back(std::move(child));
	}

	m_selectedShapes.clear();
}

void CSelectionController::DragSelected(double dx, double dy)
{
	for (IShape* shape : m_selectedShapes)
	{
		shape->Move(dx, dy);
	}
}

void CSelectionController::RemoveInvalidSelection()
{
	const auto& shapes = m_shapeController.GetShapes();
	m_selectedShapes.erase(
		std::remove_if(m_selectedShapes.begin(), m_selectedShapes.end(),
			[&shapes](IShape* s) {
				return std::find_if(shapes.begin(), shapes.end(),
						   [s](const std::unique_ptr<IShape>& up) { return up.get() == s; })
					== shapes.end();
			}),
		m_selectedShapes.end());
}

std::vector<std::unique_ptr<IShape>>& CSelectionController::GetShapes()
{
	return m_shapeController.GetShapes();
}
