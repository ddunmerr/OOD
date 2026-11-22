#pragma once
#include "CModifyShapesCommand.h"
#include "IToolState.h"
#include <functional>

class CFillState : public IToolState
{
public:
	using ColorGetter = std::function<uint32_t()>;
	using ThicknessGetter = std::function<double()>;

	CFillState(ColorGetter getOutline, ColorGetter getFill, ThicknessGetter getThickness);
	bool HandleEvent(const sf::Event& event, CSelectionController& selection) override;

private:
	ColorGetter m_getOutlineColor;
	ColorGetter m_getFillColor;
	ThicknessGetter m_getThickness;
};
