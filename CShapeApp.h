#pragma once
#include "CCanvasAdapter.h"
#include "CShapeController.h"
#include "consts.h"
#include <SFML/Graphics.hpp>
#include <iosfwd>

class CShapeApp
{
public:
	CShapeApp(std::istream& input, std::ostream& output);

	void Run();

private:
	void ProcessEvents();
	void Render();

	CShapeController m_controller;
	sf::RenderWindow m_window;
	CCanvasAdapter m_canvas;
};
