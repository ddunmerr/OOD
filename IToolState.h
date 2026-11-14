#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class CSelectionController;

class IToolState
{
public:
	virtual ~IToolState() = default;

	virtual bool HandleEvent(const sf::Event& event,
		CSelectionController& editor)
		= 0;
	virtual std::string GetName() const = 0;
};
