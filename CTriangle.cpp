#include "CTriangle.h"
#include "ShapeFormatter.h"

const double TWO = 2.0;
const std::string COLON = ": ";

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3,
	uint32_t outlineColor, uint32_t fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CTriangle::GetSideLength(const CPoint& point1, const CPoint& point2) const
{
	double dx = point2.GetX() - point1.GetX();
	double dy = point2.GetY() - point1.GetY();
	return std::sqrt(dx * dx + dy * dy);
}

double CTriangle::GetArea() const
{
	double a = GetSideLength(m_vertex1, m_vertex2);
	double b = GetSideLength(m_vertex2, m_vertex3);
	double c = GetSideLength(m_vertex3, m_vertex1);
	double p = (a + b + c) / TWO;
	return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

double CTriangle::GetPerimeter() const
{
	return GetSideLength(m_vertex1, m_vertex2) + GetSideLength(m_vertex2, m_vertex3) + GetSideLength(m_vertex3, m_vertex1);
}

std::string CTriangle::ToString() const
{
	return FormatShape(TRIANGLE, *this);
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.FillPolygon({ m_vertex1, m_vertex2, m_vertex3 }, m_fillColor);

	canvas.DrawLine(m_vertex1, m_vertex2, m_outlineColor);
	canvas.DrawLine(m_vertex2, m_vertex3, m_outlineColor);
	canvas.DrawLine(m_vertex3, m_vertex1, m_outlineColor);
}

CPoint CTriangle::GetVertex1() const { return m_vertex1; }
CPoint CTriangle::GetVertex2() const { return m_vertex2; }
CPoint CTriangle::GetVertex3() const { return m_vertex3; }

bool CTriangle::ContainsPoint(const CPoint& point) const
{
	const double d1 = (point.GetX() - m_vertex2.GetX()) * (m_vertex1.GetY() - m_vertex2.GetY()) - (m_vertex1.GetX() - m_vertex2.GetX()) * (point.GetY() - m_vertex2.GetY());
	const double d2 = (point.GetX() - m_vertex3.GetX()) * (m_vertex2.GetY() - m_vertex3.GetY()) - (m_vertex2.GetX() - m_vertex3.GetX()) * (point.GetY() - m_vertex3.GetY());
	const double d3 = (point.GetX() - m_vertex1.GetX()) * (m_vertex3.GetY() - m_vertex1.GetY()) - (m_vertex3.GetX() - m_vertex1.GetX()) * (point.GetY() - m_vertex1.GetY());

	const bool hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	const bool hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(hasNeg && hasPos);
}

CRectD CTriangle::GetBounds() const
{
	const double left = std::min({ m_vertex1.GetX(), m_vertex2.GetX(), m_vertex3.GetX() });
	const double right = std::max({ m_vertex1.GetX(), m_vertex2.GetX(), m_vertex3.GetX() });
	const double top = std::min({ m_vertex1.GetY(), m_vertex2.GetY(), m_vertex3.GetY() });
	const double bottom = std::max({ m_vertex1.GetY(), m_vertex2.GetY(), m_vertex3.GetY() });
	return { left, top, right, bottom };
}

void CTriangle::Move(double dx, double dy)
{
	m_vertex1 = CPoint(m_vertex1.GetX() + dx, m_vertex1.GetY() + dy);
	m_vertex2 = CPoint(m_vertex2.GetX() + dx, m_vertex2.GetY() + dy);
	m_vertex3 = CPoint(m_vertex3.GetX() + dx, m_vertex3.GetY() + dy);
}
