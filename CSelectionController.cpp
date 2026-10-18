#include "CSelectionController.h"
#include "consts.h"
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

namespace
{
const uint32_t SELECTION_FRAME_COLOR = 0x4D6BFE;
const uint32_t SELECTION_MARKER_COLOR = 0x4D6BFE;
const double MARKER_SIZE = 6.0;
const double MARKER_HALF = MARKER_SIZE / 2.0;
const std::size_t MIN_SHAPES_FOR_GROUP = 2;
const std::size_t SINGLE_SELECTED_SHAPE = 1;
const double ZERO_DELTA = 0.0;
} // namespace

CSelectionController::CSelectionController(CShapeController& shapeController)
	: m_shapeController(shapeController)
{
}

void CSelectionController::HandleEvent(const sf::Event& event)
{
	if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mousePressed->button == sf::Mouse::Button::Left)
		{
			const bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);
			SelectShapeAt(CPoint(mousePressed->position.x, mousePressed->position.y), shift);

			if (!m_selectedShapes.empty())
			{
				m_isDragging = true;
				m_lastMousePos = sf::Vector2f(static_cast<float>(mousePressed->position.x),
					static_cast<float>(mousePressed->position.y));
			}
		}
	}
	else if (const auto* mouseReleased = event.getIf<sf::Event::MouseButtonReleased>())
	{
		if (mouseReleased->button == sf::Mouse::Button::Left)
		{
			m_isDragging = false;
		}
	}
	else if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>())
	{
		if (m_isDragging)
		{
			const sf::Vector2f current(static_cast<float>(mouseMoved->position.x),
				static_cast<float>(mouseMoved->position.y));
			const double dx = current.x - m_lastMousePos.x;
			const double dy = current.y - m_lastMousePos.y;
			DragSelected(dx, dy);
			m_lastMousePos = current;
		}
	}
	else if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
	{
		const bool ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);
		if (ctrl && keyPressed->code == sf::Keyboard::Key::G)
		{
			GroupSelected();
		}
		else if (ctrl && keyPressed->code == sf::Keyboard::Key::U)
		{
			UngroupSelected();
		}
	}
}

void CSelectionController::DrawSelection(ICanvas& canvas) const
{
	for (const IShape* shape : m_selectedShapes)
	{
		const CRectD bounds = shape->GetBounds();
		const CPoint topLeft(bounds.left, bounds.top);
		const CPoint bottomRight(bounds.right, bounds.bottom);

		canvas.DrawRect(topLeft, bottomRight, SELECTION_FRAME_COLOR);

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

	auto& shapes = m_shapeController.GetShapesMutable();
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

	auto& shapes = m_shapeController.GetShapesMutable();
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
