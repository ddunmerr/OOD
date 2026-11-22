#include "CAddShapeState.h"
#include "CSelectionController.h"

CAddShapeState::CAddShapeState(std::string name, Creator creator)
	: m_name(std::move(name))
	, m_creator(std::move(creator))
{
}

bool CAddShapeState::HandleEvent(const sf::Event& event, CSelectionController& selection)
{
	if (auto* mp = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mp->button == sf::Mouse::Button::Left && m_creator)
		{
			sf::Vector2f pos(static_cast<float>(mp->position.x), static_cast<float>(mp->position.y));
			auto shape = m_creator(pos);
			if (shape)
			{
				CAddShapeCommand cmd(selection.GetShapes(), std::move(shape));
				cmd.Execute();
				return true;
			}
		}
	}
	return false;
}
