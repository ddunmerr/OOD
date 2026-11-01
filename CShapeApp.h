#pragma once
#include "CCanvasAdapter.h"
#include "CSelectionController.h"
#include "CShapeController.h"
#include "CShapeDrawer.h"
#include "consts.h"
#include <SFML/Graphics.hpp>
#include <iosfwd>

namespace
{
const sf::Color BACKGROUND_COLOR(BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B);
} // namespace

class CShapeApp
{
public:
	CShapeApp(std::istream& input, std::ostream& output);

	void Run();

private:
	void ProcessEvents();
	void Render();

	CShapeController m_controller;
	CSelectionController m_selectionController;
	sf::RenderWindow m_window;
	CCanvasAdapter m_canvas;
};
