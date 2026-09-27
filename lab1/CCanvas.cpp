#include "CCanvas.h"

namespace
{
sf::Color ToSfColor(uint32_t rgb)
{
	return sf::Color(
		static_cast<std::uint8_t>((rgb >> 16) & 0xFF),
		static_cast<std::uint8_t>((rgb >> 8) & 0xFF),
		static_cast<std::uint8_t>(rgb & 0xFF));
}

sf::Vector2f ToSfVector(CPoint point)
{
	return sf::Vector2f(
		static_cast<float>(point.GetX()),
		static_cast<float>(point.GetY()));
}
} // namespace

CCanvas::CCanvas(sf::RenderTarget& target)
	: m_target(target)
{
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor) const
{
	sf::Vertex line[] = {
		sf::Vertex(ToSfVector(from), ToSfColor(lineColor)),
		sf::Vertex(ToSfVector(to), ToSfColor(lineColor))
	};
	m_target.draw(line, 2, sf::PrimitiveType::Lines);
}

void CCanvas::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) const
{
	if (points.size() < 3)
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

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor) const
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setOrigin({ static_cast<float>(radius), static_cast<float>(radius) });
	circle.setPosition(ToSfVector(center));
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(1.0f);
	circle.setOutlineColor(ToSfColor(lineColor));
	m_target.draw(circle);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor) const
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setOrigin({ static_cast<float>(radius), static_cast<float>(radius) });
	circle.setPosition(ToSfVector(center));
	circle.setFillColor(ToSfColor(fillColor));
	m_target.draw(circle);
}
