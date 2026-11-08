#include "CToolbar.h"
#include "CCanvasAdapter.h"
#include "CCircle.h"
#include "CModifyShapesCommand.h"
#include "CRectangle.h"
#include "CSelectionController.h"
#include "CShapeController.h"
#include "CToolState.h"
#include "CTriangle.h"
#include "consts.h"
#include <functional>
#include <utility>

namespace
{
constexpr float BTN = 34.f;
constexpr float PAD = 6.f;
constexpr float Y = 6.f;
constexpr float BAR_HEIGHT = BTN + 2 * PAD;

// Цвета в формате 0xRRGGBB
constexpr uint32_t COLOR_DRAG = 0xB4DCFF;
constexpr uint32_t COLOR_FILL = 0xB4FFB4;
constexpr uint32_t COLOR_ADD = 0xFFDCB4;
constexpr uint32_t COLOR_THICK = 0xE6E6E6;

const uint32_t PALETTE[] = {
	0xFF0000, // красный
	0x00C800, // зелёный
	0x0064FF, // синий
	0xFFDC00, // жёлтый
	0x000000 // чёрный
};
constexpr std::size_t PALETTE_SIZE = 5;
} // namespace

CToolbar::CToolbar(CShapeController& controller,
	CSelectionController& selection,
	CCanvasAdapter& canvas)
	: m_controller(controller)
	, m_selection(selection)
	, m_canvas(canvas)
{
	BuildButtons();
	SetTool(CToolState::CreateDrag());
}

void CToolbar::SetTool(std::unique_ptr<ITool> tool)
{
	m_tool = std::move(tool);
}

void CToolbar::BuildButtons()
{
	auto add = [this](float x, const std::string& label, uint32_t rgb,
				   std::function<void()> onClick) {
		sf::Color c(
			static_cast<std::uint8_t>((rgb >> 16) & 0xFF),
			static_cast<std::uint8_t>((rgb >> 8) & 0xFF),
			static_cast<std::uint8_t>(rgb & 0xFF));
		auto btn = std::make_unique<CButton>(
			sf::FloatRect({ x, Y }, { BTN, BTN }), label, std::move(onClick));
		btn->SetFillColor(c);
		m_buttons.push_back(std::move(btn));
	};

	// --- Режимы ---
	add(PAD, "D", COLOR_DRAG, [this]() {
		SetTool(CToolState::CreateDrag());
		m_isFillMode = false;
	});

	add(PAD + BTN + PAD, "F", COLOR_FILL, [this]() {
		SetTool(CToolState::CreateFill(
			[this]() { return m_currentOutlineColor; },
			[this]() { return m_currentFillColor; },
			[this]() { return m_currentThickness; }));
		m_isFillMode = true;
	});

	// --- Добавление фигур ---
	add(PAD + 2 * (BTN + PAD), "T", COLOR_ADD, [this]() {
		SetTool(CToolState::CreateAddShape("T", [](sf::Vector2f p) {
			return std::make_unique<CTriangle>(
				CPoint(p.x, p.y),
				CPoint(p.x + 80, p.y),
				CPoint(p.x + 40, p.y + 80),
				DEFAULT_OUTLINE_COLOR, DEFAULT_FILL_COLOR);
		}));
		m_isFillMode = false;
	});

	add(PAD + 3 * (BTN + PAD), "R", COLOR_ADD, [this]() {
		SetTool(CToolState::CreateAddShape("R", [](sf::Vector2f p) {
			return std::make_unique<CRectangle>(
				CPoint(p.x, p.y),
				100.0, 60.0,
				DEFAULT_OUTLINE_COLOR, DEFAULT_FILL_COLOR);
		}));
		m_isFillMode = false;
	});

	add(PAD + 4 * (BTN + PAD), "C", COLOR_ADD, [this]() {
		SetTool(CToolState::CreateAddShape("C", [](sf::Vector2f p) {
			return std::make_unique<CCircle>(
				CPoint(p.x, p.y), 40.0,
				DEFAULT_OUTLINE_COLOR, DEFAULT_FILL_COLOR);
		}));
		m_isFillMode = false;
	});

	// --- Палитра ОБВОДКИ (5 цветов) ---
	for (std::size_t i = 0; i < PALETTE_SIZE; ++i)
	{
		float x = PAD + (5 + i) * (BTN + PAD);
		add(x, "", PALETTE[i], [this, i]() {
			m_currentOutlineColor = PALETTE[i];
		});
	}

	// --- Палитра ЗАЛИВКИ (5 цветов) ---
	for (std::size_t i = 0; i < PALETTE_SIZE; ++i)
	{
		float x = PAD + (10 + i) * (BTN + PAD);
		add(x, "", PALETTE[i], [this, i]() {
			m_currentFillColor = PALETTE[i];
		});
	}

	// --- Толщины ---
	add(PAD + 15 * (BTN + PAD), "1", COLOR_THICK, [this]() { m_currentThickness = 1.0; });
	add(PAD + 16 * (BTN + PAD), "3", COLOR_THICK, [this]() { m_currentThickness = 3.0; });
	add(PAD + 17 * (BTN + PAD), "5", COLOR_THICK, [this]() { m_currentThickness = 5.0; });
}

void CToolbar::HandleEvent(const sf::Event& event)
{
	if (auto* mp = event.getIf<sf::Event::MouseButtonPressed>())
	{

		if (mp->position.y < BAR_HEIGHT)
		{ /* кнопки */
			sf::Vector2f pos(mp->position.x, mp->position.y);
			for (auto& btn : m_buttons)
			{
				if (btn->Contains(pos))
				{
					btn->Click();
					return;
				}
			}
			return;
		}
	}
	if (m_tool)
		m_tool->HandleEvent(event, m_selection);
}

void CToolbar::Draw(sf::RenderWindow& window) const
{
	sf::RectangleShape bg({ static_cast<float>(WIDTH), BAR_HEIGHT });
	bg.setFillColor(sf::Color(230, 230, 230));
	window.draw(bg);

	for (const auto& btn : m_buttons)
		btn->Draw(window);
}
