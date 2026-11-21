#pragma once
#include "CCanvasAdapter.h"
#include "CSelectionController.h"
#include "CShapeController.h"
#include "CShapeDrawer.h"
#include "CToolbar.h"
#include "IShape.h"
#include "consts.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class CApplicationSingletone
{
public:
	static CApplicationSingletone& Instance();

	void Run(const std::string& inputFile);

private:
	CApplicationSingletone() = default;
	CApplicationSingletone(const CApplicationSingletone&) = delete;
	CApplicationSingletone& operator=(const CApplicationSingletone&) = delete;

	void ProcessEvents();
	void Render();

	sf::RenderWindow m_window;
	std::vector<std::unique_ptr<IShape>> m_shapes;
	std::unique_ptr<CShapeController> m_controller;
	std::unique_ptr<CSelectionController> m_selectionController;
	std::unique_ptr<CToolbar> m_toolbar;
	std::unique_ptr<CCanvasAdapter> m_canvas;
};
