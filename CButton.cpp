#include "CButton.h"

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
	if (m_onClick)
	{
		m_onClick();
	}
}

void CButton::Draw(sf::RenderWindow& window) const
{
	sf::RectangleShape rect;
	rect.setPosition(m_bounds.position);
	rect.setSize(m_bounds.size);
	rect.setFillColor(m_isOutline ? sf::Color::Transparent : m_fillColor);
	rect.setOutlineColor(m_isOutline ? m_fillColor : sf::Color(SF_GRAY, SF_GRAY, SF_GRAY));
	rect.setOutlineThickness(BUTTON_OUTLINE_THICKNESS);
	window.draw(rect);

	if (m_label.empty())
	{
		return;
	}

	static sf::Font font;
	static bool loaded = false;
	if (!loaded)
	{
		loaded = font.openFromFile(DEFAULT_FONT);
	}
	if (!loaded)
		return;

	sf::Text text(font, m_label, FONT_SIZE);
	text.setFillColor(sf::Color::Black);
	sf::FloatRect tb = text.getLocalBounds();
	text.setPosition({ m_bounds.position.x + m_bounds.size.x / POSITION_HALF - tb.size.x / POSITION_HALF,
		m_bounds.position.y + m_bounds.size.y / POSITION_HALF - tb.size.y / POSITION_HALF - POSITION_QUARTER });
	window.draw(text);
}
