#pragma once
#include "ICanvas.h"
#include "consts.h"
#include <SFML/Graphics.hpp>

namespace
{
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
const sf::Vector2f CIRCLE_ORIGIN_OFFSET{ 0.0f, 0.0f };

} // namespace

class CCanvasAdapter : public ICanvas
{
public:
	explicit CCanvasAdapter(sf::RenderTarget& target);

	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) const override;
	void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) const override;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor) const override;
	void FillCircle(CPoint center, double radius, uint32_t fillColor) const override;
	void DrawRect(CPoint topLeft, CPoint bottomRight, uint32_t lineColor) const override;
	void FillRect(CPoint topLeft, CPoint bottomRight, uint32_t fillColor) const override;

private:
	sf::RenderTarget& m_target;
};
