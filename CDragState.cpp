#include "CDragState.h"
#include "CSelectionController.h"

bool CDragState::HandleEvent(const sf::Event& event, CSelectionController& selection)
{
	if (auto* mp = event.getIf<sf::Event::MouseButtonPressed>();
		mp && mp->button == sf::Mouse::Button::Left && mp->position.y >= BAR_HEIGHT && !selection.GetSelected().empty())
	{
		m_isDragging = true;
		m_lastMousePos = sf::Vector2f(static_cast<float>(mp->position.x),
			static_cast<float>(mp->position.y));
		return true;
	}

	if (auto* mm = event.getIf<sf::Event::MouseMoved>();
		mm && m_isDragging)
	{
		sf::Vector2f pos(static_cast<float>(mm->position.x), static_cast<float>(mm->position.y));
		float dx = pos.x - m_lastMousePos.x;
		float dy = pos.y - m_lastMousePos.y;

		std::for_each(selection.GetSelected().begin(), selection.GetSelected().end(),
			[dx, dy](IShape* shape) { shape->Move(dx, dy); });

		m_lastMousePos = pos;
		return true;
	}

	if (auto* mr = event.getIf<sf::Event::MouseButtonReleased>();
		mr && mr->button == sf::Mouse::Button::Left)
	{
		m_isDragging = false;
		return true;
	}

	return false;
}
