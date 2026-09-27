#pragma once
#include "ICanvas.h"
#include "IShape.h"
#include <memory>
#include <vector>

class CShapeDrawer
{
public:
	static void DrawAll(const std::vector<std::unique_ptr<IShape>>& shapes, ICanvas& canvas);
};
