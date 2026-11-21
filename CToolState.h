#pragma once
#include "CAddShapeCommand.h"
#include "CSelectionController.h"
#include "CToolbar.h"
#include "IToolState.h"
#include "consts.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <string>
#include <utility>

class CToolState : public IToolState
{
public:
	using PressAction = std::function<bool(CSelectionController&, sf::Vector2f, bool)>;
	using Creator = std::function<std::unique_ptr<IShape>(sf::Vector2f)>;

	CToolState(std::string name, bool isDragMode, PressAction onPressed);

	bool HandleEvent(const sf::Event& event, CSelectionController& editor) override;

	static std::unique_ptr<CToolState> CreateDrag();
	static std::unique_ptr<CToolState> CreateFill(
		std::function<uint32_t()> getOutlineColor,
		std::function<uint32_t()> getFillColor,
		std::function<double()> getThickness);
	static std::unique_ptr<CToolState> CreateAddShape(std::string name, Creator creator);

private:
	std::string m_name;
	bool m_isDragMode;
	PressAction m_onPressed;
	Creator m_creator;
};
