#include "CCanvasAdapter.h"

namespace
{
const int COLOR_RED_SHIFT = 16;
const int COLOR_GREEN_SHIFT = 8;
const int COLOR_BLUE_MASK = 0xFF;
const int COLOR_CHANNEL_MASK = 0xFF;
const float OUTLINE_THICKNESS = 1.0f;
const sf::Vector2f CIRCLE_ORIGIN_OFFSET{ 0.0f, 0.0f };

sf::Color ToSfColor(uint32_t rgb)
{
	return sf::Color(
		static_cast<std::uint8_t>((rgb >> COLOR_RED_SHIFT) & COLOR_CHANNEL_MASK),
		static_cast<std::uint8_t>((rgb >> COLOR_GREEN_SHIFT) & COLOR_CHANNEL_MASK),
		static_cast<std::uint8_t>(rgb & COLOR_BLUE_MASK));
}

sf::Vector2f ToSfVector(CPoint point)
{
	return sf::Vector2f(
		static_cast<float>(point.GetX()),
		static_cast<float>(point.GetY()));
}
} // namespace

CCanvasAdapter::CCanvasAdapter(sf::RenderTarget& target)
	: m_target(target)
{
}

void CCanvasAdapter::DrawLine(CPoint from, CPoint to, uint32_t lineColor) const
{
	sf::Vertex line[] = {
		sf::Vertex(ToSfVector(from), ToSfColor(lineColor)),
		sf::Vertex(ToSfVector(to), ToSfColor(lineColor))
	};
	m_target.draw(line, 2, sf::PrimitiveType::Lines);
}

void CCanvasAdapter::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) const
{
	const std::size_t MIN_POLYGON_POINTS = 3;
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

void CCanvasAdapter::DrawCircle(CPoint center, double radius, uint32_t lineColor) const
{
	const float floatRadius = static_cast<float>(radius);
	sf::CircleShape circle(floatRadius);
	circle.setOrigin({ floatRadius, floatRadius });
	circle.setPosition(ToSfVector(center));
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(OUTLINE_THICKNESS);
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

void CCanvasAdapter::DrawRect(CPoint topLeft, CPoint bottomRight, uint32_t lineColor) const
{
	const sf::Vector2f size(
		static_cast<float>(bottomRight.GetX() - topLeft.GetX()),
		static_cast<float>(bottomRight.GetY() - topLeft.GetY()));
	sf::RectangleShape rect(size);
	rect.setPosition(ToSfVector(topLeft));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(OUTLINE_THICKNESS);
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
