#include "CApplicationSingletone.h"

CApplicationSingletone& CApplicationSingletone::Instance()
{
	static CApplicationSingletone instance;
	return instance;
}

void CApplicationSingletone::Run(const std::string& inputFile)
{
	std::ifstream inFile(inputFile);
	std::ofstream outFile(OUTPUT_FILE);
	if (!inFile.is_open() || !outFile.is_open())
	{
		std::cerr << ERROR_CANT_OPEN_FILES << std::endl;
		return;
	}
	m_controller = std::make_unique<CShapeController>(inFile, outFile);
	m_controller->Run();
	m_shapes = m_controller->TakeShapes();

	m_window.create(
		sf::VideoMode({ WIDTH, HEIGHT }),
		WINDOW_TITLE);

	m_canvas = std::make_unique<CCanvasAdapter>(m_window);
	m_selectionController = std::make_unique<CSelectionController>(*m_controller);
	m_toolbar = std::make_unique<CToolbar>(*m_controller, *m_selectionController, *m_canvas);

	while (m_window.isOpen())
	{
		ProcessEvents();
		Render();
	}
}

void CApplicationSingletone::ProcessEvents()
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

void CApplicationSingletone::Render()
{
	m_window.clear(sf::Color(BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B));
	CShapeDrawer::DrawAll(m_controller->GetShapes(), *m_canvas);
	m_selectionController->DrawSelection(*m_canvas);
	m_toolbar->Draw(m_window);
	m_window.display();
}
