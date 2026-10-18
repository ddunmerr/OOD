#include "CCompositeShape.h"
#include <algorithm>

CCompositeShape::CCompositeShape(std::vector<std::shared_ptr<IShape>> children)
	: m_children(std::move(children))
{
}

double CCompositeShape::GetArea() const
{
	double sum = 0;
	for (const auto& child : m_children)
		sum += child->GetArea();
	return sum;
}

double CCompositeShape::GetPerimeter() const
{
	double sum = 0;
	for (const auto& child : m_children)
		sum += child->GetPerimeter();
	return sum;
}

std::string CCompositeShape::ToString() const
{
	return "GROUP (contains " + std::to_string(m_children.size()) + " shapes)";
}

uint32_t CCompositeShape::GetOutlineColor() const
{
	return 0x000000; // У группы нет своего цвета
}

bool CCompositeShape::ContainsPoint(const CPoint& point) const
{
	// Группа содержит точку, если её содержит хотя бы один ребёнок
	return std::any_of(m_children.begin(), m_children.end(),
		[&point](const auto& child) { return child->ContainsPoint(point); });
}

CRectD CCompositeShape::GetBounds() const
{
	if (m_children.empty())
		return { 0, 0, 0, 0 };

	CRectD bounds = m_children[0]->GetBounds();
	for (size_t i = 1; i < m_children.size(); ++i)
	{
		CRectD childBounds = m_children[i]->GetBounds();
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
		child->Move(dx, dy);
}

void CCompositeShape::Draw(ICanvas& canvas) const
{
	for (const auto& child : m_children)
		child->Draw(canvas);
}
