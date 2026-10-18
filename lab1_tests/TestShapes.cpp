#include "stdafx.h"
#include "../CCircle.h"
#include "../CLineSegment.h"
#include "../CPoint.h"
#include "../CRectangle.h"
#include "../CShapeParser.h"
#include "../CTriangle.h"
#include "CMockCanvas.h"

BOOST_AUTO_TEST_SUITE(Point)
	BOOST_AUTO_TEST_CASE(default_is_zero)
	{
		CPoint point;
		BOOST_CHECK_EQUAL(point.GetX(), 0.0);
		BOOST_CHECK_EQUAL(point.GetY(), 0.0);
	}
	BOOST_AUTO_TEST_CASE(holds_given_coordinates)
	{
		CPoint point(3.5, -2.0);
		BOOST_CHECK_EQUAL(point.GetX(), 3.5);
		BOOST_CHECK_EQUAL(point.GetY(), -2.0);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(LineSegment)
	BOOST_AUTO_TEST_CASE(perimeter_is_length)
	{
		CLineSegment line(CPoint(0, 0), CPoint(3, 4), 0x000000);
		BOOST_CHECK_EQUAL(line.GetPerimeter(), 5.0);
	}
	BOOST_AUTO_TEST_CASE(area_is_zero)
	{
		CLineSegment line(CPoint(0, 0), CPoint(10, 10), 0x000000);
		BOOST_CHECK_EQUAL(line.GetArea(), 0.0);
	}
	BOOST_AUTO_TEST_CASE(zero_length_segment)
	{
		CLineSegment line(CPoint(5, 5), CPoint(5, 5), 0x000000);
		BOOST_CHECK_EQUAL(line.GetPerimeter(), 0.0);
	}
	BOOST_AUTO_TEST_CASE(start_and_end_points)
	{
		CLineSegment line(CPoint(1, 2), CPoint(3, 4), 0x000000);
		BOOST_CHECK_EQUAL(line.GetStartPoint().GetX(), 1.0);
		BOOST_CHECK_EQUAL(line.GetEndPoint().GetY(), 4.0);
	}
	BOOST_AUTO_TEST_CASE(outline_color_is_stored)
	{
		CLineSegment line(CPoint(0, 0), CPoint(1, 1), 0xABCDEF);
		BOOST_CHECK_EQUAL(line.GetOutlineColor(), 0xABCDEF);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Triangle)
	BOOST_AUTO_TEST_CASE(right_triangle_area)
	{
		CTriangle triangle(CPoint(0, 0), CPoint(4, 0), CPoint(0, 3), 0, 0);
		BOOST_CHECK_EQUAL(triangle.GetArea(), 6.0);
	}
	BOOST_AUTO_TEST_CASE(right_triangle_perimeter)
	{
		CTriangle triangle(CPoint(0, 0), CPoint(4, 0), CPoint(0, 3), 0, 0);
		BOOST_CHECK_EQUAL(triangle.GetPerimeter(), 12.0);
	}
	BOOST_AUTO_TEST_CASE(degenerate_triangle_zero_area)
	{
		CTriangle triangle(CPoint(0, 0), CPoint(5, 0), CPoint(10, 0), 0, 0);
		BOOST_CHECK_EQUAL(triangle.GetArea(), 0.0);
	}
	BOOST_AUTO_TEST_CASE(vertices_correct)
	{
		CTriangle triangle(CPoint(0, 0), CPoint(4, 0), CPoint(0, 3), 0, 0);
		BOOST_CHECK_EQUAL(triangle.GetVertex1().GetX(), 0.0);
		BOOST_CHECK_EQUAL(triangle.GetVertex2().GetX(), 4.0);
		BOOST_CHECK_EQUAL(triangle.GetVertex3().GetY(), 3.0);
	}
	BOOST_AUTO_TEST_CASE(colors_correct)
	{
		CTriangle triangle(CPoint(0, 0), CPoint(1, 0), CPoint(0, 1), 0x123456, 0xABCDEF);
		BOOST_CHECK_EQUAL(triangle.GetOutlineColor(), 0x123456);
		BOOST_CHECK_EQUAL(triangle.GetFillColor(), 0xABCDEF);
	}
	BOOST_AUTO_TEST_CASE(to_string_contains_perimeter_and_area)
	{
		CTriangle triangle(CPoint(0, 0), CPoint(4, 0), CPoint(0, 3), 0, 0);
		std::string str = triangle.ToString();
		BOOST_CHECK(str.find("TRIANGLE") != std::string::npos);
		BOOST_CHECK(str.find("P=12") != std::string::npos);
		BOOST_CHECK(str.find("S=6") != std::string::npos);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Rectangle)
	BOOST_AUTO_TEST_CASE(area_and_perimeter)
	{
		CRectangle rect(CPoint(0, 10), 5, 10, 0, 0);
		BOOST_CHECK_EQUAL(rect.GetArea(), 50.0);
		BOOST_CHECK_EQUAL(rect.GetPerimeter(), 30.0);
	}
	BOOST_AUTO_TEST_CASE(zero_dimensions)
	{
		CRectangle rect(CPoint(0, 0), 0, 0, 0, 0);
		BOOST_CHECK_EQUAL(rect.GetArea(), 0.0);
		BOOST_CHECK_EQUAL(rect.GetPerimeter(), 0.0);
	}
	BOOST_AUTO_TEST_CASE(right_bottom_corner)
	{
		CRectangle rect(CPoint(10, 20), 30, 40, 0, 0);
		CPoint rightBottom = rect.GetRightBottom();
		BOOST_CHECK_EQUAL(rightBottom.GetX(), 40.0);
		BOOST_CHECK_EQUAL(rightBottom.GetY(), 60.0);
	}
	BOOST_AUTO_TEST_CASE(width_and_height)
	{
		CRectangle rect(CPoint(0, 0), 15, 25, 0, 0);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 15.0);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 25.0);
	}
	BOOST_AUTO_TEST_CASE(to_string_contains_perimeter_and_area)
	{
		CRectangle rect(CPoint(0, 0), 5, 10, 0, 0);
		std::string str = rect.ToString();
		BOOST_CHECK(str.find("RECTANGLE") != std::string::npos);
		BOOST_CHECK(str.find("P=30") != std::string::npos);
		BOOST_CHECK(str.find("S=50") != std::string::npos);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle)
	BOOST_AUTO_TEST_CASE(area_and_perimeter)
	{
		CCircle circle(CPoint(0, 0), 5, 0, 0);
		BOOST_CHECK_CLOSE(circle.GetArea(), 78.5398, 0.01);
		BOOST_CHECK_CLOSE(circle.GetPerimeter(), 31.4159, 0.01);
	}
	BOOST_AUTO_TEST_CASE(zero_radius)
	{
		CCircle circle(CPoint(10, 20), 0, 0, 0);
		BOOST_CHECK_EQUAL(circle.GetArea(), 0.0);
		BOOST_CHECK_EQUAL(circle.GetPerimeter(), 0.0);
	}
	BOOST_AUTO_TEST_CASE(center_and_radius)
	{
		CCircle circle(CPoint(3.5, -2.0), 7.5, 0, 0);
		BOOST_CHECK_EQUAL(circle.GetCenter().GetX(), 3.5);
		BOOST_CHECK_EQUAL(circle.GetRadius(), 7.5);
	}
	BOOST_AUTO_TEST_CASE(to_string_contains_perimeter_and_area)
	{
		CCircle circle(CPoint(0, 0), 5, 0, 0);
		std::string str = circle.ToString();
		BOOST_CHECK(str.find("CIRCLE") != std::string::npos);
		BOOST_CHECK(str.find("P=31") != std::string::npos);
		BOOST_CHECK(str.find("S=79") != std::string::npos);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ShapeDraw)

	// Отрезок вызывает DrawLine с правильным цветом
	BOOST_AUTO_TEST_CASE(line_segment_draws_one_line)
	{
		CLineSegment line(CPoint(0, 0), CPoint(3, 4), 0x123456);
		CMockCanvas canvas;

		line.Draw(canvas);

		BOOST_REQUIRE_EQUAL(canvas.calls.size(), 1);
		BOOST_CHECK_EQUAL(canvas.calls[0].method, "DrawLine");
		BOOST_CHECK_EQUAL(canvas.calls[0].color, 0x123456);
	}

	// Треугольник: заливка полигоном из 3 точек + 3 линии обводки
	BOOST_AUTO_TEST_CASE(triangle_fills_polygon_and_draws_outline)
	{
		CTriangle triangle(CPoint(0, 0), CPoint(4, 0), CPoint(0, 3), 0xAAAAAA, 0xBBBBBB);
		CMockCanvas canvas;

		triangle.Draw(canvas);

		BOOST_REQUIRE_EQUAL(canvas.calls.size(), 4);
		BOOST_CHECK_EQUAL(canvas.calls[0].method, "FillPolygon");
		BOOST_CHECK_EQUAL(canvas.calls[0].pointCount, 3);
		BOOST_CHECK_EQUAL(canvas.calls[0].color, 0xBBBBBB);

		for (int i = 1; i <= 3; ++i)
		{
			BOOST_CHECK_EQUAL(canvas.calls[i].method, "DrawLine");
			BOOST_CHECK_EQUAL(canvas.calls[i].color, 0xAAAAAA);
		}
	}

	// Прямоугольник: заливка полигоном из 4 точек + 4 линии обводки
	BOOST_AUTO_TEST_CASE(rectangle_fills_polygon_and_draws_outline)
	{
		CRectangle rect(CPoint(0, 0), 5, 10, 0xAAAAAA, 0xBBBBBB);
		CMockCanvas canvas;

		rect.Draw(canvas);

		BOOST_REQUIRE_EQUAL(canvas.calls.size(), 5);
		BOOST_CHECK_EQUAL(canvas.calls[0].method, "FillPolygon");
		BOOST_CHECK_EQUAL(canvas.calls[0].pointCount, 4);
		BOOST_CHECK_EQUAL(canvas.calls[0].color, 0xBBBBBB);

		for (int i = 1; i <= 4; ++i)
		{
			BOOST_CHECK_EQUAL(canvas.calls[i].method, "DrawLine");
			BOOST_CHECK_EQUAL(canvas.calls[i].color, 0xAAAAAA);
		}
	}

	// Круг: заливка + обводка
	BOOST_AUTO_TEST_CASE(circle_fills_and_draws_circle)
	{
		CCircle circle(CPoint(10, 20), 5, 0xAAAAAA, 0xBBBBBB);
		CMockCanvas canvas;

		circle.Draw(canvas);

		BOOST_REQUIRE_EQUAL(canvas.calls.size(), 2);
		BOOST_CHECK_EQUAL(canvas.calls[0].method, "FillCircle");
		BOOST_CHECK_EQUAL(canvas.calls[0].color, 0xBBBBBB);
		BOOST_CHECK_EQUAL(canvas.calls[1].method, "DrawCircle");
		BOOST_CHECK_EQUAL(canvas.calls[1].color, 0xAAAAAA);
	}

	// Полиморфизм: через IShape* все фигуры рисуются правильно
	BOOST_AUTO_TEST_CASE(polymorphic_draw_through_IShape)
	{
		std::vector<std::unique_ptr<IShape>> shapes;
		shapes.push_back(std::make_unique<CLineSegment>(CPoint(0, 0), CPoint(3, 4), 0));
		shapes.push_back(std::make_unique<CCircle>(CPoint(0, 0), 5, 0, 0));
		shapes.push_back(std::make_unique<CTriangle>(CPoint(0, 0), CPoint(4, 0), CPoint(0, 3), 0, 0));

		CMockCanvas canvas;
		for (const auto& shape : shapes)
		{
			shape->Draw(canvas);
		}

		BOOST_REQUIRE_EQUAL(canvas.calls.size(), 1 + 2 + 4);
		BOOST_CHECK_EQUAL(canvas.calls[0].method, "DrawLine");
		BOOST_CHECK_EQUAL(canvas.calls[1].method, "FillCircle");
		BOOST_CHECK_EQUAL(canvas.calls[2].method, "DrawCircle");
		BOOST_CHECK_EQUAL(canvas.calls[3].method, "FillPolygon");
	}

BOOST_AUTO_TEST_SUITE_END()
