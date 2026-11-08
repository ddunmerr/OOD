#include "CCanvasAdapter.h"

CCanvasAdapter::CCanvasAdapter(sf::RenderTarget& target)
	: m_target(target)
{
}

void CCanvasAdapter::DrawLine(CPoint from, CPoint to, uint32_t lineColor, double thickness) const
{
	if (thickness <= 0.0)
		thickness = 1.0;
	const double dx = to.GetX() - from.GetX();
	const double dy = to.GetY() - from.GetY();
	const double len = std::sqrt(dx * dx + dy * dy);
	if (len == 0.0)
		return;

	const double nx = -dy / len * thickness / 2.0;
	const double ny = dx / len * thickness / 2.0;

	sf::ConvexShape quad;
	quad.setPointCount(4);
	quad.setPoint(0, ToSfVector(CPoint(from.GetX() + nx, from.GetY() + ny)));
	quad.setPoint(1, ToSfVector(CPoint(to.GetX() + nx, to.GetY() + ny)));
	quad.setPoint(2, ToSfVector(CPoint(to.GetX() - nx, to.GetY() - ny)));
	quad.setPoint(3, ToSfVector(CPoint(from.GetX() - nx, from.GetY() - ny)));
	quad.setFillColor(ToSfColor(lineColor));
	m_target.draw(quad);
}
void CCanvasAdapter::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) const
{
	if (points.size() < MIN_POLYGON_POINTS)
	{
		return;
	}

	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	for (std::size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(i, ToSfVector(points[i]));
	}
	polygon.setFillColor(ToSfColor(fillColor));
	m_target.draw(polygon);
}

void CCanvasAdapter::DrawCircle(CPoint center, double radius, uint32_t lineColor, double thickness) const
{
	const float floatRadius = static_cast<float>(radius);
	sf::CircleShape circle(floatRadius);
	circle.setOrigin({ floatRadius, floatRadius });
	circle.setPosition(ToSfVector(center));
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(thickness);
	circle.setOutlineColor(ToSfColor(lineColor));
	m_target.draw(circle);
}

void CCanvasAdapter::FillCircle(CPoint center, double radius, uint32_t fillColor) const
{
	const float floatRadius = static_cast<float>(radius);
	sf::CircleShape circle(floatRadius);
	circle.setOrigin({ floatRadius, floatRadius });
	circle.setPosition(ToSfVector(center));
	circle.setFillColor(ToSfColor(fillColor));
	m_target.draw(circle);
}

void CCanvasAdapter::DrawRect(CPoint topLeft, CPoint bottomRight, uint32_t lineColor, double thickness) const
{
	const sf::Vector2f size(
		static_cast<float>(bottomRight.GetX() - topLeft.GetX()),
		static_cast<float>(bottomRight.GetY() - topLeft.GetY()));
	sf::RectangleShape rect(size);
	rect.setPosition(ToSfVector(topLeft));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(thickness);
	rect.setOutlineColor(ToSfColor(lineColor));
	m_target.draw(rect);
}

void CCanvasAdapter::FillRect(CPoint topLeft, CPoint bottomRight, uint32_t fillColor) const
{
	const sf::Vector2f size(
		static_cast<float>(bottomRight.GetX() - topLeft.GetX()),
		static_cast<float>(bottomRight.GetY() - topLeft.GetY()));
	sf::RectangleShape rect(size);
	rect.setPosition(ToSfVector(topLeft));
	rect.setFillColor(ToSfColor(fillColor));
	m_target.draw(rect);
}

void CCanvasAdapter::DrawPolygon(const std::vector<CPoint>& points, uint32_t lineColor, double thickness) const
{
	if (points.size() < 3)
		return;
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	for (size_t i = 0; i < points.size(); ++i)
		polygon.setPoint(i, ToSfVector(points[i]));
	polygon.setFillColor(sf::Color::Transparent);
	polygon.setOutlineThickness(static_cast<float>(thickness));
	polygon.setOutlineColor(ToSfColor(lineColor));
	m_target.draw(polygon);
}
