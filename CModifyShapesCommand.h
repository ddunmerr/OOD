#pragma once
#include "ICommand.h"
#include "IShape.h"
#include <functional>
#include <utility>
#include <vector>

class CModifyShapesCommand : public ICommand
{
public:
	using Action = std::function<void(IShape*)>;

	CModifyShapesCommand(const std::vector<IShape*>& shapes, Action action);
	void Execute() override;

private:
	std::vector<IShape*> m_shapes;
	Action m_action;
};
