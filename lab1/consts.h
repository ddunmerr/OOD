#pragma once
#include <string>

// Типы фигур
const std::string TRIANGLE = "TRIANGLE";
const std::string RECTANGLE = "RECTANGLE";
const std::string CIRCLE = "CIRCLE";
const std::string LINE_SEGMENT = "LINE";

// Префиксы координат
const std::string PREFIX_P1 = "P1";
const std::string PREFIX_P2 = "P2";
const std::string PREFIX_P3 = "P3";
const std::string PREFIX_CENTER = "C";
const std::string PREFIX_RADIUS = "R";

// Разделители и форматирование
const std::string COLON_SPACE = ": ";
const std::string SEPARATOR = "; ";
const std::string EQUALS = "=";
const std::string COMMA = ",";
const std::string SEMICOLON = ";";

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

// Цвета по умолчанию (не используются в выводе, но нужны конструкторам)
const uint32_t DEFAULT_OUTLINE_COLOR = 0x000000;
const uint32_t DEFAULT_FILL_COLOR = 0xFFF3FF;
