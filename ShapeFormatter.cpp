#include "ShapeFormatter.h"
#include "consts.h"
#include <iomanip>
#include <sstream>

std::string FormatShape(const std::string& typeName, const IShape& shape)
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(0)
		<< typeName << COLON_SPACE
		<< PERIMETER_PREFIX << shape.GetPerimeter()
		<< SEPARATOR
		<< AREA_PREFIX << shape.GetArea();
	return oss.str();
}
