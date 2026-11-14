#include "CAddShapeCommand.h"

CAddShapeCommand::CAddShapeCommand(std::vector<std::unique_ptr<IShape>>& shapes,
	std::unique_ptr<IShape> newShape)
	: m_shapes(shapes)
	, m_newShape(std::move(newShape))
{
}

void CAddShapeCommand::Execute()
{
	m_shapes.push_back(std::move(m_newShape));
}
