#include "CToolbar.h"
#include "CAddShapeState.h"
#include "CCircle.h"
#include "CDragState.h"
#include "CFillState.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include <memory>
#include <utility>

CToolbar::CToolbar(CShapeController& controller,
	CSelectionController& selection,
	CCanvasAdapter& canvas)
	: m_controller(controller)
	, m_selection(selection)
	, m_canvas(canvas)
{
	BuildButtons();
	SetTool(std::make_unique<CDragState>());
}

void CToolbar::SetTool(std::unique_ptr<IToolState> tool)
{
	m_tool = std::move(tool);
}

void CToolbar::BuildButtons()
{
	auto addButton = [&](float x, const std::string& label, uint32_t rgb, auto onClick) {
		sf::Color c(
			GET_RED(rgb),
			GET_GREEN(rgb),
			GET_BLUE(rgb));
		auto btn = std::make_unique<CButton>(
			sf::FloatRect({ x, Y }, { BTN, BTN }), label, std::move(onClick));
		btn->SetFillColor(c);
		m_buttons.push_back(std::move(btn));
	};

	// 1. РЕЖИМЫ РАБОТЫ
	addButton(PAD, DRAG_BUTTON_LABEL, COLOR_DRAG, [this]() {
		SetTool(std::make_unique<CDragState>());
		m_isFillMode = false;
	});

	addButton(PAD + BTN + PAD, FILL_BUTTON_LABEL, COLOR_FILL, [this]() {
		SetTool(std::make_unique<CFillState>(
			[this]() { return m_currentOutlineColor; },
			[this]() { return m_currentFillColor; },
			[this]() { return m_currentThickness; }));
		m_isFillMode = true;
	});

	// 2. ДОБАВЛЕНИЕ ФИГУР
	addButton(PAD + 2 * (BTN + PAD), TRIANGLE_BUTTON_LABEL, COLOR_ADD, [this]() {
		SetTool(std::make_unique<CAddShapeState>(TRIANGLE_BUTTON_LABEL, [](sf::Vector2f p) {
			return std::make_unique<CTriangle>(
				CPoint(p.x, p.y),
				CPoint(p.x + TRIANGLE_DEFAULT_SIZE, p.y),
				CPoint(p.x + TRIANGLE_OFFSET_X, p.y + TRIANGLE_DEFAULT_SIZE),
				DEFAULT_OUTLINE_COLOR, DEFAULT_FILL_COLOR);
		}));
		m_isFillMode = false;
	});

	addButton(PAD + 3 * (BTN + PAD), RECTANGLE_BUTTON_LABEL, COLOR_ADD, [this]() {
		SetTool(std::make_unique<CAddShapeState>(RECTANGLE_BUTTON_LABEL, [](sf::Vector2f p) {
			return std::make_unique<CRectangle>(
				CPoint(p.x, p.y),
				RECTANGLE_DEFAULT_WIDTH, RECTANGLE_DEFAULT_HEIGHT,
				DEFAULT_OUTLINE_COLOR, DEFAULT_FILL_COLOR);
		}));
		m_isFillMode = false;
	});

	addButton(PAD + 4 * (BTN + PAD), CIRCLE_BUTTON_LABEL, COLOR_ADD, [this]() {
		SetTool(std::make_unique<CAddShapeState>(CIRCLE_BUTTON_LABEL, [](sf::Vector2f p) {
			return std::make_unique<CCircle>(
				CPoint(p.x, p.y), CIRCLE_DEFAULT_RADIUS,
				DEFAULT_OUTLINE_COLOR, DEFAULT_FILL_COLOR);
		}));
		m_isFillMode = false;
	});

	// 3. ПАЛИТРА ЦВЕТОВ ОБВОДКИ
	for (std::size_t i = 0; i < PALETTE_SIZE; ++i)
	{
		float x = PAD + (PALETTE_OUTLINE_START_INDEX + i) * (BTN + PAD);
		addButton(x, "", PALETTE[i], [this, i]() {
			m_currentOutlineColor = PALETTE[i];
		});
	}

	// 4. ПАЛИТРА ЦВЕТОВ ЗАЛИВКИ
	for (std::size_t i = 0; i < PALETTE_SIZE; ++i)
	{
		float x = PAD + (PALETTE_FILL_START_INDEX + i) * (BTN + PAD);
		addButton(x, "", PALETTE[i], [this, i]() {
			m_currentFillColor = PALETTE[i];
		});
	}

	// 5. ТОЛЩИНА ЛИНИИ
	addButton(PAD + THICKNESS_BUTTONS_START_INDEX * (BTN + PAD), THIN_THICK_BUTTON_LABEL, COLOR_THICK, [this]() {
		m_currentThickness = THIN_THICKNESS;
	});
	addButton(PAD + (THICKNESS_BUTTONS_START_INDEX + 1) * (BTN + PAD), MID_THICK_BUTTON_LABEL, COLOR_THICK, [this]() {
		m_currentThickness = MID_THICKNESS;
	});
	addButton(PAD + (THICKNESS_BUTTONS_START_INDEX + 2) * (BTN + PAD), FAT_BUTTON_LABEL, COLOR_THICK, [this]() {
		m_currentThickness = FAT_THICKNESS;
	});
}

void CToolbar::HandleEvent(const sf::Event& event)
{
	// 1. Сначала проверяем, не кликнули ли мы по кнопкам самой панели
	if (auto* mp = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mp->position.y < BAR_HEIGHT)
		{
			sf::Vector2f pos(static_cast<float>(mp->position.x), static_cast<float>(mp->position.y));
			for (auto& btn : m_buttons)
			{
				if (btn->Contains(pos))
				{
					btn->Click();
					return; // Событие обработано кнопкой, дальше не передаем
				}
			}
			return; // Клик в пустую область панели, игнорируем
		}
	}

	// 2. Если клик был по рабочему полю, передаем событие текущему инструменту (State)
	if (m_tool)
	{
		m_tool->HandleEvent(event, m_selection);
	}
}

void CToolbar::Draw(sf::RenderWindow& window) const
{
	// Рисуем фон панели
	sf::RectangleShape bg({ static_cast<float>(WIDTH), BAR_HEIGHT });
	bg.setFillColor(sf::Color(BACKGROUND_GRAY, BACKGROUND_GRAY, BACKGROUND_GRAY));
	window.draw(bg);

	// Рисуем все кнопки поверх фона
	for (const auto& btn : m_buttons)
	{
		btn->Draw(window);
	}
}
