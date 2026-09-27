#include "CRectangle.h"

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
	return 2.0 * (m_width + m_height);
}

std::string CRectangle::ToString() const
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(0)
		<< RECTANGLE << COLON_SPACE
		<< PERIMETER_PREFIX << GetPerimeter()
		<< SEPARATOR
		<< AREA_PREFIX << GetArea();
	return oss.str();
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
