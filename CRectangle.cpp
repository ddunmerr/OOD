#include "CRectangle.h"

CRectangle::CRectangle(const CPoint& leftTop, double width, double height,
	uint32_t outlineColor, uint32_t fillColor)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
	, m_outlineThickness(THIN_THICKNESS)
{
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return TWO_DOUBLE * (m_width + m_height);
}

std::string CRectangle::ToString() const
{
	CShapeFormatter formatter;
	return formatter.FormatShape(RECTANGLE_STRING, *this);
}

void CRectangle::Draw(ICanvas& canvas) const
{
	const CPoint rightBottom(m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height);
	canvas.FillRect(m_leftTop, rightBottom, m_fillColor);
	canvas.DrawRect(m_leftTop, rightBottom, m_outlineColor, m_outlineThickness);
}

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

uint32_t CRectangle::GetOutlineColor() const { return m_outlineColor; }
uint32_t CRectangle::GetFillColor() const { return m_fillColor; }
CPoint CRectangle::GetLeftTop() const { return m_leftTop; }

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height);
}

double CRectangle::GetWidth() const { return m_width; }
double CRectangle::GetHeight() const { return m_height; }

void CRectangle::SetOutlineColor(uint32_t color) { m_outlineColor = color; }
void CRectangle::SetFillColor(uint32_t color) { m_fillColor = color; }
void CRectangle::SetOutlineThickness(double thickness) { m_outlineThickness = thickness; }
