#pragma once
#include "IToolState.h"

class CDragState : public IToolState
{
public:
	CDragState() = default;
	bool HandleEvent(const sf::Event& event, CSelectionController& editor) override;

private:
	bool m_isDragging = false;
	sf::Vector2f m_lastMousePos;
};
