#pragma once
#include "CCompositeShape.h"
#include "CShapeController.h"
#include <SFML/Window/Event.hpp>
#include <memory>
#include <vector>

class CSelectionController
{
public:
	explicit CSelectionController(CShapeController& shapeController);

	void HandleEvent(const sf::Event& event);

	void DrawSelection(ICanvas& canvas) const;

private:
	CShapeController& m_shapeController;

	std::vector<IShape*> m_selectedShapes;

	bool m_isDragging = false;
	sf::Vector2f m_lastMousePos;

	void SelectShapeAt(CPoint point, bool shiftPressed);
	void ClearSelection();
	void GroupSelected();
	void UngroupSelected();
	void DragSelected(double dx, double dy);
	void RemoveInvalidSelection();

	IShape* FindTopmostShapeAt(CPoint point) const;
};
