#pragma once
#include "IShape.h"
#include "consts.h"
#include <iomanip>
#include <sstream>
#include <string>

std::string FormatShape(const std::string& typeName, const IShape& shape);
