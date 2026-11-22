#include "CCompositeShape.h"
#include <algorithm>

CCompositeShape::CCompositeShape(uint32_t outlineColor, uint32_t fillColor)
	: m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CCompositeShape::GetArea() const
{
	double total = EMPTY_BOUNDS_VALUE;
	for (const auto& child : m_children)
	{
		total += child->GetArea();
	}
	return total;
}

double CCompositeShape::GetPerimeter() const
{
	double total = EMPTY_BOUNDS_VALUE;
	for (const auto& child : m_children)
	{
		total += child->GetPerimeter();
	}
	return total;
}

std::string CCompositeShape::ToString() const
{
	return std::string("") + std::to_string(m_children.size());
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
	return std::any_of(m_children.begin(), m_children.end(),
		[&point](const auto& child) {
			return child->ContainsPoint(point);
		});
}

CRectD CCompositeShape::GetBounds() const
{
	if (m_children.empty())
	{
		return { EMPTY_BOUNDS_VALUE, EMPTY_BOUNDS_VALUE,
			EMPTY_BOUNDS_VALUE, EMPTY_BOUNDS_VALUE };
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
	std::for_each(m_children.begin(), m_children.end(),
		[dx, dy](const auto& child) {
			child->Move(dx, dy);
		});
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

void CCompositeShape::SetOutlineColor(uint32_t color)
{
	std::for_each(m_children.begin(), m_children.end(),
		[color](const auto& child) {
			child->SetOutlineColor(color);
		});
}
void CCompositeShape::SetFillColor(uint32_t color)
{
	std::for_each(m_children.begin(), m_children.end(),
		[color](const auto& child) {
			child->SetFillColor(color);
		});
}
void CCompositeShape::SetOutlineThickness(double thickness)
{

	std::for_each(m_children.begin(), m_children.end(),
		[thickness](const auto& child) {
			child->SetOutlineThickness(thickness);
		});
}
