#pragma once
#include "CAddShapeCommand.h"
#include "IToolState.h"
#include <functional>
#include <string>

class CAddShapeState : public IToolState
{
public:
	using Creator = std::function<std::unique_ptr<IShape>(sf::Vector2f)>;

	CAddShapeState(std::string name, Creator creator);
	bool HandleEvent(const sf::Event& event, CSelectionController& selection) override;

private:
	std::string m_name;
	Creator m_creator;
};
