#pragma once
#include "ISolidShape.h"
#include "consts.h"
#include <algorithm>
#include <limits>
#include <memory>
#include <vector>

class CCompositeShape : public ISolidShape
{
public:
	explicit CCompositeShape(uint32_t outlineColor = DEFAULT_OUTLINE_COLOR, uint32_t fillColor = DEFAULT_FILL_COLOR);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;

	void Draw(ICanvas& canvas) const override;

	bool ContainsPoint(const CPoint& point) const override;
	CRectD GetBounds() const override;
	void Move(double dx, double dy) override;

	void Add(std::unique_ptr<IShape> shape);
	std::vector<std::unique_ptr<IShape>> ReleaseChildren();
	const std::vector<std::unique_ptr<IShape>>& GetChildren() const;

private:
	std::vector<std::unique_ptr<IShape>> m_children;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};
