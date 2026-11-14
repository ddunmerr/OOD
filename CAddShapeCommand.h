#pragma once
#include "ICommand.h"
#include "IShape.h"
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

class CAddShapeCommand : public ICommand
{
public:
	CAddShapeCommand(std::vector<std::unique_ptr<IShape>>& shapes,
		std::unique_ptr<IShape> newShape);
	void Execute() override;

private:
	std::vector<std::unique_ptr<IShape>>& m_shapes;
	std::unique_ptr<IShape> m_newShape;
};
