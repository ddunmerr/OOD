#include "stdafx.h"
#include "../lab4/CCircle.h"
#include "../lab4/CLineSegment.h"
#include "../lab4/CPoint.h"
#include "../lab4/CRectangle.h"
#include "../lab4/CShapeParser.h"
#include "../lab4/CTriangle.h"

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

BOOST_AUTO_TEST_SUITE(ShapeParser)
	BOOST_AUTO_TEST_CASE(parse_line)
	{
		auto shape = CShapeParser::ParseCommand("LINE: P1=0,0; P2=3,4");
		BOOST_REQUIRE(shape != nullptr);
		BOOST_CHECK_EQUAL(shape->GetPerimeter(), 5.0);
	}
	BOOST_AUTO_TEST_CASE(parse_triangle)
	{
		auto shape = CShapeParser::ParseCommand("TRIANGLE: P1=0,0; P2=4,0; P3=0,3");
		BOOST_REQUIRE(shape != nullptr);
		BOOST_CHECK_EQUAL(shape->GetArea(), 6.0);
	}
	BOOST_AUTO_TEST_CASE(parse_rectangle)
	{
		auto shape = CShapeParser::ParseCommand("RECTANGLE: P1=200,200; P2=300,300");
		BOOST_REQUIRE(shape != nullptr);
		BOOST_CHECK_EQUAL(shape->GetArea(), 10000.0);
	}
	BOOST_AUTO_TEST_CASE(parse_circle)
	{
		auto shape = CShapeParser::ParseCommand("CIRCLE: C=100,100; R=50");
		BOOST_REQUIRE(shape != nullptr);
		BOOST_CHECK_CLOSE(shape->GetArea(), 7853.98, 0.01);
	}
	BOOST_AUTO_TEST_CASE(parse_rectangle_with_reversed_points)
	{
		auto shape = CShapeParser::ParseCommand("RECTANGLE: P1=300,300; P2=200,200");
		BOOST_REQUIRE(shape != nullptr);
		BOOST_CHECK_EQUAL(shape->GetArea(), 10000.0);
	}
	BOOST_AUTO_TEST_CASE(negative_coordinates_are_valid)
	{
		auto shape = CShapeParser::ParseCommand("LINE: P1=-1,-2; P2=-4,-6");
		BOOST_REQUIRE(shape != nullptr);
		BOOST_CHECK_EQUAL(shape->GetPerimeter(), 5.0);
	}
BOOST_AUTO_TEST_SUITE_END()
