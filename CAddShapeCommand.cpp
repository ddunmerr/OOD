#include "CAddShapeCommand.h"
#include <iostream>
#include <utility>

CAddShapeCommand::CAddShapeCommand(std::vector<std::unique_ptr<IShape>>& shapes,
	std::unique_ptr<IShape> newShape)
	: m_shapes(shapes)
	, m_newShape(std::move(newShape))
{
}

void CAddShapeCommand::Execute()
{
	std::cout << "[AddShapeCommand] push, before size=" << m_shapes.size() << std::endl;

	m_shapes.push_back(std::move(m_newShape));

	std::cout << "[AddShapeCommand] after size=" << m_shapes.size() << std::endl;
}
