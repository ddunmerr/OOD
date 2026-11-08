#pragma once
#include "ICanvasDrawable.h"
#include <cstdint>
#include <string>

struct CRectD
{
	double left, top, right, bottom;
};

class IShape : public ICanvasDrawable
{
public:
	virtual ~IShape() override = default;

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;

	virtual bool ContainsPoint(const CPoint& point) const = 0;
	virtual CRectD GetBounds() const = 0;
	virtual void Move(double dx, double dy) = 0;

	virtual void SetOutlineColor(uint32_t color) = 0;
	virtual void SetFillColor(uint32_t color) = 0;
	virtual void SetOutlineThickness(double thickness) = 0;
};
