#pragma once
#include "CCompositeShape.h"
#include "CShapeController.h"
#include "consts.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <memory>
#include <vector>

class CSelectionController
{
public:
	explicit CSelectionController(CShapeController& shapeController);

	void HandleEvent(const sf::Event& event);
	void DrawSelection(ICanvas& canvas) const;

	const std::vector<IShape*>& GetSelected() const { return m_selectedShapes; }
	std::vector<std::unique_ptr<IShape>>& GetShapes();

	void SelectShapeAt(CPoint point, bool shiftPressed);
	IShape* FindTopmostShapeAt(CPoint point) const;

private:
	CShapeController& m_shapeController;
	std::vector<IShape*> m_selectedShapes;

	void HandleMouseButtonPressed(const sf::Event::MouseButtonPressed& event);
	void HandleKeyPressed(const sf::Event::KeyPressed& event);

	void ClearSelection();
	void GroupSelected();
	void UngroupSelected();
};
