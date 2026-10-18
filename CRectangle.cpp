#include "CRectangle.h"
#include "ShapeFormatter.h"

const double TWO = 2.0;

CRectangle::CRectangle(const CPoint& leftTop, double width, double height,
	uint32_t outlineColor, uint32_t fillColor)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return TWO * (m_width + m_height);
}

std::string CRectangle::ToString() const
{
	return FormatShape(RECTANGLE, *this);
}

void CRectangle::Draw(ICanvas& canvas) const
{
	const CPoint rightTop(m_leftTop.GetX() + m_width, m_leftTop.GetY());
	const CPoint rightBottom(m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height);
	const CPoint leftBottom(m_leftTop.GetX(), m_leftTop.GetY() + m_height);

	canvas.FillPolygon({ m_leftTop, rightTop, rightBottom, leftBottom }, m_fillColor);

	canvas.DrawLine(m_leftTop, rightTop, m_outlineColor);
	canvas.DrawLine(rightTop, rightBottom, m_outlineColor);
	canvas.DrawLine(rightBottom, leftBottom, m_outlineColor);
	canvas.DrawLine(leftBottom, m_leftTop, m_outlineColor);
}

uint32_t CRectangle::GetOutlineColor() const { return m_outlineColor; }
uint32_t CRectangle::GetFillColor() const { return m_fillColor; }
CPoint CRectangle::GetLeftTop() const { return m_leftTop; }

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height);
}

double CRectangle::GetWidth() const { return m_width; }
double CRectangle::GetHeight() const { return m_height; }

bool CRectangle::ContainsPoint(const CPoint& point) const
{
	return point.GetX() >= m_leftTop.GetX() && point.GetX() <= m_leftTop.GetX() + m_width && point.GetY() >= m_leftTop.GetY() && point.GetY() <= m_leftTop.GetY() + m_height;
}

CRectD CRectangle::GetBounds() const
{
	return { m_leftTop.GetX(), m_leftTop.GetY(),
		m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height };
}

void CRectangle::Move(double dx, double dy)
{
	m_leftTop = CPoint(m_leftTop.GetX() + dx, m_leftTop.GetY() + dy);
}
