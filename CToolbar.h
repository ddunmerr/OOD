#pragma once
#include "CButton.h"
#include "CToolState.h"
#include "ITool.h"
#include "consts.h"
#include <functional>
#include <memory>
#include <vector>

class CShapeController;
class CSelectionController;
class CCanvasAdapter;

class CToolbar
{
public:
	CToolbar(CShapeController& controller,
		CSelectionController& selection,
		CCanvasAdapter& canvas);

	void HandleEvent(const sf::Event& event);
	void Draw(sf::RenderWindow& window) const;

	bool IsFillMode() const { return m_isFillMode; }

	// void SetOutlineColor(uint32_t color);
	// void SetFillColor(uint32_t color);
	// void SetThickness(double t);

	uint32_t GetOutlineColor() const { return m_currentOutlineColor; }
	uint32_t GetFillColor() const { return m_currentFillColor; }
	double GetThickness() const { return m_currentThickness; }

private:
	void BuildButtons();
	void SetTool(std::unique_ptr<ITool> tool);

	CShapeController& m_controller;
	CSelectionController& m_selection;
	CCanvasAdapter& m_canvas;

	std::unique_ptr<ITool> m_tool;
	std::vector<std::unique_ptr<CButton>> m_buttons;
	bool m_isFillMode = false;

	uint32_t m_currentOutlineColor = DEFAULT_OUTLINE_COLOR;
	uint32_t m_currentFillColor = DEFAULT_FILL_COLOR;
	double m_currentThickness = 1.0;
};
