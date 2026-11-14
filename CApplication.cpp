#include "CApplication.h"

Application& Application::Instance()
{
	static Application instance;
	return instance;
}

void Application::Run(const std::string& inputFile)
{
	// 1) Загружаем фигуры через контроллер (Fasade: вся логика чтения/вывода).
	m_controller = std::make_unique<CShapeController>(std::cin, std::cout);
	m_controller->Run();
	m_shapes = m_controller->TakeShapes();

	// 2) Окно.
	m_window.create(
		sf::VideoMode({ WIDTH, HEIGHT }),
		WINDOW_TITLE);

	m_canvas = std::make_unique<CCanvasAdapter>(m_window);
	m_selectionController = std::make_unique<CSelectionController>(*m_controller);
	m_toolbar = std::make_unique<CToolbar>(*m_controller, *m_selectionController, *m_canvas);

	// 3) Цикл.
	while (m_window.isOpen())
	{
		ProcessEvents();
		Render();
	}
}

void Application::ProcessEvents()
{
	while (auto event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_window.close();
			continue;
		}
		m_toolbar->HandleEvent(*event);
		m_selectionController->HandleEvent(*event);
	}
}

void Application::Render()
{
	m_window.clear(sf::Color(BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B));
	CShapeDrawer::DrawAll(m_controller->GetShapes(), *m_canvas);
	m_selectionController->DrawSelection(*m_canvas);
	m_toolbar->Draw(m_window);
	m_window.display();
}
