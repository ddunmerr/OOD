#pragma once
#include "CButton.h"
#include "CCanvasAdapter.h"
#include "CCircle.h"
#include "CModifyShapesCommand.h"
#include "CRectangle.h"
#include "CSelectionController.h"
#include "CShapeController.h"
#include "CTriangle.h"
#include "IToolState.h"
#include "consts.h"
#include <functional>
#include <memory>
#include <utility>
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

	uint32_t GetOutlineColor() const { return m_currentOutlineColor; }
	uint32_t GetFillColor() const { return m_currentFillColor; }
	double GetThickness() const { return m_currentThickness; }

private:
	void BuildButtons();
	void SetTool(std::unique_ptr<IToolState> tool);

	CShapeController& m_controller;
	CSelectionController& m_selection;
	CCanvasAdapter& m_canvas;

	std::unique_ptr<IToolState> m_tool;
	std::vector<std::unique_ptr<CButton>> m_buttons;
	bool m_isFillMode = false;

	uint32_t m_currentOutlineColor = DEFAULT_OUTLINE_COLOR;
	uint32_t m_currentFillColor = DEFAULT_FILL_COLOR;
	double m_currentThickness = THIN_THICKNESS;
};
