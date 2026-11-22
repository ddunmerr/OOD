#include "CFillState.h"
#include "CSelectionController.h"

CFillState::CFillState(ColorGetter getOutline, ColorGetter getFill, ThicknessGetter getThickness)
	: m_getOutlineColor(std::move(getOutline))
	, m_getFillColor(std::move(getFill))
	, m_getThickness(std::move(getThickness))
{
}

bool CFillState::HandleEvent(const sf::Event& event, CSelectionController& selection)
{
	if (auto* mp = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mp->button == sf::Mouse::Button::Left)
		{
			IShape* hit = selection.FindTopmostShapeAt(CPoint(mp->position.x, mp->position.y));
			if (hit)
			{
				CModifyShapesCommand cmd({ hit }, [&](IShape* s) {
					s->SetOutlineColor(m_getOutlineColor());
					s->SetFillColor(m_getFillColor());
					s->SetOutlineThickness(m_getThickness());
				});
				cmd.Execute();
				return true;
			}
		}
	}
	return false;
}
