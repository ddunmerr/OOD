#pragma once
#include "CCircle.h"
#include "CLineSegment.h"
#include "CPoint.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "IShape.h"
#include "consts.h"
#include <limits>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

class CShapeParser
{
public:
	static std::unique_ptr<IShape> ParseCommand(const std::string& line);

private:
	static CPoint ParsePoint(std::istringstream& iss, const std::string& expectedPrefix);
	static void SkipSeparator(std::istringstream& iss);
};
