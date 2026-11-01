#include "ShapeFormatter.h"

std::string FormatShape(const std::string& typeName, const IShape& shape)
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(0)
		<< typeName << COLON_STRING
		<< PERIMETER_PREFIX << shape.GetPerimeter()
		<< SEPARATOR_STRING
		<< AREA_PREFIX << shape.GetArea();
	return oss.str();
}
