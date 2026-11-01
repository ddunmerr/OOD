#include "CShapeParser.h"

CPoint CShapeParser::ParsePoint(std::istringstream& iss, const std::string& expectedPrefix)
{
	std::string token;
	double x = 0.0;
	double y = 0.0;

	if (!std::getline(iss, token, EQUAL_CHAR) || token != expectedPrefix)
	{
		throw std::runtime_error(ERROR_INVALID_POINT_PREFIX);
	}

	if (!(iss >> x))
	{
		throw std::runtime_error(ERROR_INVALID_X);
	}

	iss.ignore(std::numeric_limits<std::streamsize>::max(), COMMA_CHAR);

	if (!(iss >> y))
	{
		throw std::runtime_error(ERROR_INVALID_Y);
	}

	return CPoint(x, y);
}

void CShapeParser::SkipSeparator(std::istringstream& iss)
{
	iss.ignore(std::numeric_limits<std::streamsize>::max(), SEMICOLON_CHAR);
	iss >> std::ws;
}

std::unique_ptr<IShape> CShapeParser::ParseCommand(const std::string& line)
{
	std::istringstream iss(line);
	std::string shapeType;

	if (!std::getline(iss, shapeType, COLON_CHAR))
	{
		return nullptr;
	}

	iss >> std::ws;

	if (shapeType == TRIANGLE_STRING)
	{
		CPoint v1 = ParsePoint(iss, PREFIX_P1);
		SkipSeparator(iss);
		CPoint v2 = ParsePoint(iss, PREFIX_P2);
		SkipSeparator(iss);
		CPoint v3 = ParsePoint(iss, PREFIX_P3);

		return std::make_unique<CTriangle>(v1, v2, v3, DEFAULT_OUTLINE_COLOR, DEFAULT_FILL_COLOR);
	}
	else if (shapeType == RECTANGLE_STRING)
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
	else if (shapeType == CIRCLE_STRING)
	{
		CPoint center = ParsePoint(iss, PREFIX_CENTER);
		SkipSeparator(iss);

		std::string token;
		double radius = ZERO_DOUBLE;

		if (!std::getline(iss, token, EQUAL_CHAR) || token != PREFIX_RADIUS)
		{
			return nullptr;
		}
		if (!(iss >> radius))
		{
			return nullptr;
		}

		return std::make_unique<CCircle>(center, radius, DEFAULT_OUTLINE_COLOR, DEFAULT_FILL_COLOR);
	}
	else if (shapeType == LINE_SEGMENT_STRING)
	{
		CPoint p1 = ParsePoint(iss, PREFIX_P1);
		SkipSeparator(iss);
		CPoint p2 = ParsePoint(iss, PREFIX_P2);

		return std::make_unique<CLineSegment>(p1, p2, DEFAULT_OUTLINE_COLOR);
	}

	return nullptr;
}
