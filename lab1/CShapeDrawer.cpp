#include "CShapeDrawer.h"

void CShapeDrawer::DrawAll(const std::vector<std::unique_ptr<IShape>>& shapes, ICanvas& canvas)
{
	for (const auto& shape : shapes)
	{
		shape->Draw(canvas);
	}
}
