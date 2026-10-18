#include "CShapeApp.h"
#include "CShapeDrawer.h"
#include <SFML/Graphics.hpp>

namespace
{
const sf::Color BACKGROUND_COLOR(240, 240, 240);
}

CShapeApp::CShapeApp(std::istream& input, std::ostream& output)
	: m_controller(input, output)
	, m_selectionController(m_controller)
	, m_window(sf::VideoMode({ WIDTH, HEIGHT }), WINDOW_TITLE)
	, m_canvas(m_window)
{
}

void CShapeApp::Run()
{
	m_controller.Run();

	while (m_window.isOpen())
	{
		ProcessEvents();
		Render();
	}
}

void CShapeApp::ProcessEvents()
{
	while (auto event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_window.close();
			continue;
		}

		m_selectionController.HandleEvent(*event);
	}
}

void CShapeApp::Render()
{
	m_window.clear(BACKGROUND_COLOR);
	CShapeDrawer::DrawAll(m_controller.GetShapes(), m_canvas);
	m_selectionController.DrawSelection(m_canvas);
	m_window.display();
}
