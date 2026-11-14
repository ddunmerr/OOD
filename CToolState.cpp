#include "CToolState.h"

CToolState::CToolState(std::string name, bool isDragMode, PressAction onPressed)
	: m_name(std::move(name))
	, m_isDragMode(isDragMode)
	, m_onPressed(std::move(onPressed))
{
}

bool CToolState::HandleEvent(const sf::Event& event, CSelectionController& editor)
{

	if (auto* mp = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mp->button != sf::Mouse::Button::Left)
			return false;
		sf::Vector2f pos(static_cast<float>(mp->position.x),
			static_cast<float>(mp->position.y));

		if (m_creator)
		{
			auto shape = m_creator(pos);
			if (shape)
			{
				CAddShapeCommand cmd(editor.GetShapes(), std::move(shape));
				cmd.Execute();
			}
			return true;
		}
		if (m_onPressed)
		{
			bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);
			return m_onPressed(editor, pos, shift);
		}
	}
	return false;
}

std::string CToolState::GetName() const { return m_name; }

std::unique_ptr<CToolState> CToolState::CreateDrag()
{
	return std::make_unique<CToolState>(DRAG_STATE, true, nullptr);
}

std::unique_ptr<CToolState> CToolState::CreateFill(
	std::function<uint32_t()> getOutlineColor,
	std::function<uint32_t()> getFillColor,
	std::function<double()> getThickness)
{
	return std::make_unique<CToolState>(
		FILL_STATE, false,
		[getOutlineColor, getFillColor, getThickness](
			CSelectionController& editor, sf::Vector2f pos, bool /*shift*/) -> bool {
			IShape* hit = editor.FindTopmostShapeAt(CPoint(pos.x, pos.y));
			if (!hit)
			{
				return false;
			}

			CModifyShapesCommand cmd({ hit }, [&](IShape* s) {
				s->SetOutlineColor(getOutlineColor());
				s->SetFillColor(getFillColor());
				s->SetOutlineThickness(getThickness());
			});
			cmd.Execute();

			return true;
		});
}

std::unique_ptr<CToolState> CToolState::CreateAddShape(std::string name, Creator creator)
{
	auto tool = std::make_unique<CToolState>(std::move(name), false, nullptr);
	tool->m_creator = std::move(creator);
	return tool;
}
