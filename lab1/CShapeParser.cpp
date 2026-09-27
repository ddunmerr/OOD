#include "CShapeParser.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CPoint.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "consts.h"
#include <limits>
#include <sstream>
#include <stdexcept>

namespace
{
CPoint ParsePoint(std::istringstream& iss, const std::string& expectedPrefix)
{
	std::string token;
	double x = 0.0;
	double y = 0.0;

	if (!std::getline(iss, token, '=') || token != expectedPrefix)
	{
		throw std::runtime_error(ERROR_INVALID_POINT_PREFIX);
	}

	if (!(iss >> x))
	{
		throw std::runtime_error(ERROR_INVALID_X);
	}

	iss.ignore(std::numeric_limits<std::streamsize>::max(), ',');

	if (!(iss >> y))
	{
		throw std::runtime_error(ERROR_INVALID_Y);
	}

	return CPoint(x, y);
}

void SkipSeparator(std::istringstream& iss)
{
	iss.ignore(std::numeric_limits<std::streamsize>::max(), ';');
	iss >> std::ws;
}
} // namespace

std::unique_ptr<IShape> CShapeParser::ParseCommand(const std::string& line)
{
	std::istringstream iss(line);
	std::string shapeType;

	if (!std::getline(iss, shapeType, ':'))
	{
		return nullptr;
	}

	iss >> std::ws;

	if (shapeType == TRIANGLE)
	{
		CPoint v1 = ParsePoint(iss, PREFIX_P1);
		SkipSeparator(iss);
		CPoint v2 = ParsePoint(iss, PREFIX_P2);
		SkipSeparator(iss);
		CPoint v3 = ParsePoint(iss, PREFIX_P3);

		return std::make_unique<CTriangle>(v1, v2, v3, DEFAULT_OUTLINE_COLOR, DEFAULT_FILL_COLOR);
	}
	else if (shapeType == RECTANGLE)
	{
		CPoint p1 = ParsePoint(iss, PREFIX_P1);
		SkipSeparator(iss);
		CPoint p2 = ParsePoint(iss, PREFIX_P2);

		double left = std::min(p1.GetX(), p2.GetX());
		double top = std::min(p1.GetY(), p2.GetY());
		double width = std::abs(p2.GetX() - p1.GetX());
		double height = std::abs(p2.GetY() - p1.GetY());

		CPoint leftTop(left, top);

		return std::make_unique<CRectangle>(leftTop, width, height, DEFAULT_OUTLINE_COLOR, DEFAULT_FILL_COLOR);
	}
	else if (shapeType == CIRCLE)
	{
		CPoint center = ParsePoint(iss, PREFIX_CENTER);
		SkipSeparator(iss);

		std::string token;
		double radius = 0.0;

		if (!std::getline(iss, token, '=') || token != PREFIX_RADIUS)
		{
			return nullptr;
		}
		if (!(iss >> radius))
		{
			return nullptr;
		}

		return std::make_unique<CCircle>(center, radius, DEFAULT_OUTLINE_COLOR, DEFAULT_FILL_COLOR);
	}
	else if (shapeType == LINE_SEGMENT)
	{
		CPoint p1 = ParsePoint(iss, PREFIX_P1);
		SkipSeparator(iss);
		CPoint p2 = ParsePoint(iss, PREFIX_P2);

		return std::make_unique<CLineSegment>(p1, p2, DEFAULT_OUTLINE_COLOR);
	}

	return nullptr;
}
