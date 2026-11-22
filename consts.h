#pragma once
#include <string>

// Типы фигур
const std::string TRIANGLE_STRING = "TRIANGLE";
const std::string RECTANGLE_STRING = "RECTANGLE";
const std::string CIRCLE_STRING = "CIRCLE";

// Префиксы координат
const std::string PREFIX_P1 = "P1";
const std::string PREFIX_P2 = "P2";
const std::string PREFIX_P3 = "P3";
const std::string PREFIX_CENTER = "C";
const std::string PREFIX_RADIUS = "R";

// Разделители и форматирование
const std::string COLON_STRING = ": ";
const std::string SEPARATOR_STRING = "; ";
const std::string EQUAL_STRING = "=";
const std::string COMMA_STRING = ",";
const std::string SEMICOLON_STRING = ";";

// Метрики
const std::string PERIMETER_PREFIX = "P=";
const std::string AREA_PREFIX = "S=";

//
const std::string INPUT_FILE = "input.txt";
const std::string OUTPUT_FILE = "output.txt";

// Сообщения об ошибках
const std::string ERROR_UNKNOWN_COMMAND = "Unknown command: ";
const std::string ERROR_NO_SHAPES = "No shapes entered.";
const std::string ERROR_INVALID_POINT_PREFIX = "Invalid point prefix";
const std::string ERROR_INVALID_X = "Invalid x coordinate";
const std::string ERROR_INVALID_Y = "Invalid y coordinate";
const std::string ERROR_INVALID_RADIUS = "Invalid radius";
const std::string ERROR_CANT_OPEN_FILES = "Error opening files!";

// Цвета по умолчанию
const uint32_t DEFAULT_OUTLINE_COLOR = 0x000000;
const uint32_t DEFAULT_FILL_COLOR = 0xFFF3FF;

// Окно
const int WIDTH = 1280;
const int HEIGHT = 600;
const std::string WINDOW_TITLE = "Shapes";

// SFML
const int COLOR_RED_SHIFT = 16;
const int COLOR_GREEN_SHIFT = 8;
const int COLOR_BLUE_MASK = 0xFF;
const int COLOR_CHANNEL_MASK = 0xFF;
const int BACKGROUND_COLOR_R = 240;
const int BACKGROUND_COLOR_G = 240;
const int BACKGROUND_COLOR_B = 240;
const int QUAD_POINTS_COUNT = 4;
const int QUAD_FIRST_POINT = 0;
const int QUAD_SECOND_POINT = 1;
const int QUAD_THIRD_POINT = 2;
const int QUAD_FOURTH_POINT = 3;

// ToolBar
const int SF_GRAY = 80;
const int FONT_SIZE = 14;
const float BUTTON_OUTLINE_THICKNESS = 1.f;
const float POSITION_HALF = 2.f;
const float POSITION_QUARTER = 4.f;
const std::string DEFAULT_FONT = "arial.ttf";

constexpr std::uint8_t GET_RED(std::uint32_t rgb)
{
	return static_cast<std::uint8_t>((rgb >> 16) & 0xFF);
}

constexpr std::uint8_t GET_GREEN(std::uint32_t rgb)
{
	return static_cast<std::uint8_t>((rgb >> 8) & 0xFF);
}

constexpr std::uint8_t GET_BLUE(std::uint32_t rgb)
{
	return static_cast<std::uint8_t>(rgb & 0xFF);
}
const uint32_t PALETTE[] = {
	0xFF0000, // красный
	0x00C800, // зелёный
	0x0064FF, // синий
	0xFFDC00, // жёлтый
	0x000000 // чёрный
};
const std::size_t PALETTE_SIZE = 5;

const std::string DRAG_BUTTON_LABEL = "D";
const std::string FILL_BUTTON_LABEL = "F";
const std::string TRIANGLE_BUTTON_LABEL = "T";
const std::string RECTANGLE_BUTTON_LABEL = "R";
const std::string CIRCLE_BUTTON_LABEL = "C";
const std::string THIN_THICK_BUTTON_LABEL = "1";
const std::string MID_THICK_BUTTON_LABEL = "3";
const std::string FAT_BUTTON_LABEL = "5";

const int THIN_THICKNESS = 1;
const int MID_THICKNESS = 3;
const int FAT_THICKNESS = 5;

// Цвета в формате 0xRRGGBB
const uint32_t COLOR_DRAG = 0xB4DCFF;
const uint32_t COLOR_FILL = 0xB4FFB4;
const uint32_t COLOR_ADD = 0xFFDCB4;
const uint32_t COLOR_THICK = 0xE6E6E6;

const float BTN = 34.f;
const float PAD = 6.f;
const float Y = 6.f;
const float BAR_HEIGHT = BTN + 2.f * PAD;

const int BACKGROUND_GRAY = 230;
const float TRIANGLE_DEFAULT_SIZE = 80.0f;
const float TRIANGLE_OFFSET_X = 40.0f;
const float RECTANGLE_DEFAULT_WIDTH = 100.0f;
const float RECTANGLE_DEFAULT_HEIGHT = 60.0f;
const float CIRCLE_DEFAULT_RADIUS = 40.0f;

const int PALETTE_OUTLINE_START_INDEX = 5;
const int PALETTE_FILL_START_INDEX = 10;
const int THICKNESS_BUTTONS_START_INDEX = 15;

const std::string DRAG_STATE = "Drag";
const std::string FILL_STATE = "Fill";

//  doubles and ints
const int ZERO_INT = 0;
const int MIN_POINTS = 3;
const double ZERO_DOUBLE = 0.0;
const double ONE_DOUBLE = 1.0;
const double TWO_DOUBLE = 2.0;
const double CLICK_TOLERANCE = 6.0;
const double CLICK_TOLERANCE_SQ = CLICK_TOLERANCE * CLICK_TOLERANCE;
const double EMPTY_BOUNDS_VALUE = ZERO_DOUBLE;
const std::size_t MIN_POLYGON_POINTS = 3;

// Selection
const uint32_t SELECTION_FRAME_COLOR = 0x4D6BFE;
const uint32_t SELECTION_MARKER_COLOR = 0x4D6BFE;
const double MARKER_SIZE = 6.0;
const double MARKER_HALF = MARKER_SIZE / 2.0;
const std::size_t MIN_SHAPES_FOR_GROUP = 2;
const std::size_t SINGLE_SELECTED_SHAPE = 1;
const double ZERO_DELTA = 0.0;

// Chars
const char EQUAL_CHAR = '=';
const char COMMA_CHAR = ',';
const char SEMICOLON_CHAR = ';';
const char COLON_CHAR = ':';
