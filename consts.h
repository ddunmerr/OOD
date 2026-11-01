#pragma once
#include <string>

// Типы фигур
const std::string TRIANGLE_STRING = "TRIANGLE";
const std::string RECTANGLE_STRING = "RECTANGLE";
const std::string CIRCLE_STRING = "CIRCLE";
const std::string LINE_SEGMENT_STRING = "LINE";

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

// Сообщения об ошибках
const std::string ERROR_UNKNOWN_COMMAND = "Unknown command: ";
const std::string ERROR_NO_SHAPES = "No shapes entered.";
const std::string ERROR_INVALID_POINT_PREFIX = "Invalid point prefix";
const std::string ERROR_INVALID_X = "Invalid x coordinate";
const std::string ERROR_INVALID_Y = "Invalid y coordinate";
const std::string ERROR_INVALID_RADIUS = "Invalid radius";

// Цвета по умолчанию
const uint32_t DEFAULT_OUTLINE_COLOR = 0x000000;
const uint32_t DEFAULT_FILL_COLOR = 0xFFF3FF;

// Окно
const int WIDTH = 800;
const int HEIGHT = 600;
const std::string WINDOW_TITLE = "Shapes";

// SFML
const int COLOR_RED_SHIFT = 16;
const int COLOR_GREEN_SHIFT = 8;
const int COLOR_BLUE_MASK = 0xFF;
const int COLOR_CHANNEL_MASK = 0xFF;
const float OUTLINE_THICKNESS = 1.0f;
const int BACKGROUND_COLOR_R = 240;
const int BACKGROUND_COLOR_G = 240;
const int BACKGROUND_COLOR_B = 240;

// doubles and ints
const int ZERO_INT = 0;
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
