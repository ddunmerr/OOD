#include "CCircle.h"
#include "ShapeFormatter.h"

const double TWO = 2.0;

CCircle::CCircle(const CPoint& center, double radius,
	uint32_t outlineColor, uint32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CCircle::GetArea() const
{
	return std::numbers::pi * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return TWO * std::numbers::pi * m_radius;
}

std::string CCircle::ToString() const
{
	return FormatShape(CIRCLE, *this);
}

void CCircle::Draw(ICanvas& canvas) const
{
	canvas.FillCircle(m_center, m_radius, m_fillColor);
	canvas.DrawCircle(m_center, m_radius, m_outlineColor);
}

uint32_t CCircle::GetOutlineColor() const { return m_outlineColor; }
uint32_t CCircle::GetFillColor() const { return m_fillColor; }
CPoint CCircle::GetCenter() const { return m_center; }
double CCircle::GetRadius() const { return m_radius; }

bool CCircle::ContainsPoint(const CPoint& point) const
{
	const double dx = point.GetX() - m_center.GetX();
	const double dy = point.GetY() - m_center.GetY();
	return (dx * dx + dy * dy) <= (m_radius * m_radius);
}

CRectD CCircle::GetBounds() const
{
	return { m_center.GetX() - m_radius, m_center.GetY() - m_radius,
		m_center.GetX() + m_radius, m_center.GetY() + m_radius };
}

void CCircle::Move(double dx, double dy)
{
	m_center = CPoint(m_center.GetX() + dx, m_center.GetY() + dy);
}
