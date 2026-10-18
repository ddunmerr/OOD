#include "CCompositeShape.h"
#include <algorithm>
#include <limits>

CCompositeShape::CCompositeShape(uint32_t outlineColor, uint32_t fillColor)
	: m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CCompositeShape::GetArea() const
{
	double total = 0.0;
	for (const auto& child : m_children)
	{
		total += child->GetArea();
	}
	return total;
}

double CCompositeShape::GetPerimeter() const
{
	double total = 0.0;
	for (const auto& child : m_children)
	{
		total += child->GetPerimeter();
	}
	return total;
}

std::string CCompositeShape::ToString() const
{
	return "GROUP: shapes=" + std::to_string(m_children.size());
}

uint32_t CCompositeShape::GetOutlineColor() const { return m_outlineColor; }
uint32_t CCompositeShape::GetFillColor() const { return m_fillColor; }

void CCompositeShape::Draw(ICanvas& canvas) const
{
	for (const auto& child : m_children)
	{
		child->Draw(canvas);
	}
}

bool CCompositeShape::ContainsPoint(const CPoint& point) const
{
	for (const auto& child : m_children)
	{
		if (child->ContainsPoint(point))
		{
			return true;
		}
	}
	return false;
}

CRectD CCompositeShape::GetBounds() const
{
	if (m_children.empty())
	{
		return { 0.0, 0.0, 0.0, 0.0 };
	}

	CRectD bounds = m_children.front()->GetBounds();
	for (const auto& child : m_children)
	{
		CRectD childBounds = child->GetBounds();
		bounds.left = std::min(bounds.left, childBounds.left);
		bounds.top = std::min(bounds.top, childBounds.top);
		bounds.right = std::max(bounds.right, childBounds.right);
		bounds.bottom = std::max(bounds.bottom, childBounds.bottom);
	}
	return bounds;
}

void CCompositeShape::Move(double dx, double dy)
{
	for (const auto& child : m_children)
	{
		child->Move(dx, dy);
	}
}

void CCompositeShape::Add(std::unique_ptr<IShape> shape)
{
	m_children.push_back(std::move(shape));
}

std::vector<std::unique_ptr<IShape>> CCompositeShape::ReleaseChildren()
{
	return std::move(m_children);
}

const std::vector<std::unique_ptr<IShape>>& CCompositeShape::GetChildren() const
{
	return m_children;
}
