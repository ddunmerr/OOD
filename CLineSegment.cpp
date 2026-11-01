#include "CLineSegment.h"

CLineSegment::CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{
}

double CLineSegment::GetArea() const
{
	return ZERO_DOUBLE;
}

double CLineSegment::GetPerimeter() const
{
	double dx = m_endPoint.GetX() - m_startPoint.GetX();
	double dy = m_endPoint.GetY() - m_startPoint.GetY();
	return std::sqrt(dx * dx + dy * dy);
}

std::string CLineSegment::ToString() const
{
	return FormatShape(LINE_SEGMENT_STRING, *this);
}

void CLineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}

bool CLineSegment::ContainsPoint(const CPoint& point) const
{
	const double ax = m_startPoint.GetX();
	const double ay = m_startPoint.GetY();
	const double bx = m_endPoint.GetX();
	const double by = m_endPoint.GetY();
	const double px = point.GetX();
	const double py = point.GetY();

	const double dx = bx - ax;
	const double dy = by - ay;
	const double lengthSq = dx * dx + dy * dy;

	double t = ZERO_DOUBLE;
	if (lengthSq > ZERO_DOUBLE)
	{
		t = ((px - ax) * dx + (py - ay) * dy) / lengthSq;
		t = std::max(ZERO_DOUBLE, std::min(ONE_DOUBLE, t));
	}

	const double cx = ax + t * dx;
	const double cy = ay + t * dy;
	const double distSq = (px - cx) * (px - cx) + (py - cy) * (py - cy);

	return distSq <= CLICK_TOLERANCE_SQ;
}

CRectD CLineSegment::GetBounds() const
{
	return { std::min(m_startPoint.GetX(), m_endPoint.GetX()),
		std::min(m_startPoint.GetY(), m_endPoint.GetY()),
		std::max(m_startPoint.GetX(), m_endPoint.GetX()),
		std::max(m_startPoint.GetY(), m_endPoint.GetY()) };
}

void CLineSegment::Move(double dx, double dy)
{
	m_startPoint = CPoint(m_startPoint.GetX() + dx, m_startPoint.GetY() + dy);
	m_endPoint = CPoint(m_endPoint.GetX() + dx, m_endPoint.GetY() + dy);
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}
