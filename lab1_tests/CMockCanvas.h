#pragma once
#include "../ICanvas.h"
#include <string>
#include <vector>

class CMockCanvas : public ICanvas
{
public:
	struct Call
	{
		std::string method;
		int pointCount = 0;
		uint32_t color = 0;
	};

	mutable std::vector<Call> calls;

	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) const override
	{
		calls.push_back({ "DrawLine", 2, lineColor });
	}

	void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) const override
	{
		calls.push_back({ "FillPolygon", static_cast<int>(points.size()), fillColor });
	}

	void DrawCircle(CPoint center, double radius, uint32_t lineColor) const override
	{
		calls.push_back({ "DrawCircle", 1, lineColor });
	}

	void FillCircle(CPoint center, double radius, uint32_t fillColor) const override
	{
		calls.push_back({ "FillCircle", 1, fillColor });
	}

	void DrawRect(CPoint topLeft, CPoint bottomRight, uint32_t lineColor) const override
	{
		calls.push_back({ "DrawRect", 2, lineColor });
	}

	void FillRect(CPoint topLeft, CPoint bottomRight, uint32_t fillColor) const override
	{
		calls.push_back({ "FillRect", 2, fillColor });
	}
};
