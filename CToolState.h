#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <string>

#include "ITool.h"

class CSelectionController;
class IShape;

class CToolState : public ITool
{
public:
	using PressAction = std::function<bool(CSelectionController&, sf::Vector2f, bool)>;
	using Creator = std::function<std::unique_ptr<IShape>(sf::Vector2f)>;

	CToolState(std::string name, bool isDragMode, PressAction onPressed);

	bool HandleEvent(const sf::Event& event, CSelectionController& editor) override;
	std::string GetName() const override;

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

	bool m_isDragging = false;
	sf::Vector2f m_lastMousePos;
};
