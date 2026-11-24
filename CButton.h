#pragma once
#include "consts.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <utility>

class CButton
{
public:
	CButton(sf::FloatRect bounds, const std::string& label, std::function<void()> onClick);

	bool Contains(sf::Vector2f pos) const;
	void Click();
	void SetFillColor(sf::Color c) { m_fillColor = c; }
	void SetOutlineMode(bool outline) { m_isOutline = outline; }

	void Draw(sf::RenderWindow& window) const;
	const sf::FloatRect& bounds() const { return m_bounds; }

private:
	sf::FloatRect m_bounds;
	std::string m_label;
	std::function<void()> m_onClick;
	sf::Color m_fillColor = sf::Color(BUTTON_FILL, BUTTON_FILL, BUTTON_FILL);
	bool m_isOutline = false;
};
