#include "CModifyShapesCommand.h"
#include <utility>

CModifyShapesCommand::CModifyShapesCommand(const std::vector<IShape*>& shapes, Action action)
	: m_shapes(shapes)
	, m_action(std::move(action))
{
}

void CModifyShapesCommand::Execute()
{
	if (!m_action)
		return;
	for (IShape* s : m_shapes)
	{
		if (s)
			m_action(s);
	}
}
