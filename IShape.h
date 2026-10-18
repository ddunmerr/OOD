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

	// Новое для лабы 2:
	virtual bool ContainsPoint(const CPoint& point) const = 0; // Попадание клика
	virtual CRectD GetBounds() const = 0; // Габариты для рамки выделения
	virtual void Move(double dx, double dy) = 0; // Перемещение фигуры
};
