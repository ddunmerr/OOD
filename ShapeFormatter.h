#pragma once
#include "IShape.h"
#include "consts.h"
#include <iomanip>
#include <sstream>
#include <string>

class CShapeFormatter
{
public:
	std::string FormatShape(const std::string& typeName, const IShape& shape);
};
