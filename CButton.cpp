#include "CButton.h"
#include "consts.h"
#include <iostream>
#include <utility>

CButton::CButton(sf::FloatRect bounds, const std::string& label, std::function<void()> onClick)
	: m_bounds(bounds)
	, m_label(label)
	, m_onClick(std::move(onClick))
{
}

bool CButton::Contains(sf::Vector2f pos) const
{
	return m_bounds.contains(pos);
}

void CButton::Click()
{
	std::cout << "[CButton] click, hasHandler=" << (m_onClick ? 1 : 0) << std::endl;
	if (m_onClick)
		m_onClick();
}

void CButton::Draw(sf::RenderWindow& window) const
{
	sf::RectangleShape rect;
	rect.setPosition(m_bounds.position);
	rect.setSize(m_bounds.size);
	rect.setFillColor(m_isOutline ? sf::Color::Transparent : m_fillColor);
	rect.setOutlineColor(m_isOutline ? m_fillColor : sf::Color(80, 80, 80));
	rect.setOutlineThickness(m_isOutline ? 3.f : 1.f);
	window.draw(rect);

	if (m_label.empty())
		return;

	static sf::Font font;
	static bool loaded = false;
	if (!loaded)
	{
		loaded = font.openFromFile("arial.ttf");
	}
	if (!loaded)
		return;

	sf::Text text(font, m_label, 14);
	text.setFillColor(sf::Color::Black);
	sf::FloatRect tb = text.getLocalBounds();
	text.setPosition({ m_bounds.position.x + m_bounds.size.x / 2.f - tb.size.x / 2.f,
		m_bounds.position.y + m_bounds.size.y / 2.f - tb.size.y / 2.f - 4.f });
	window.draw(text);
}
