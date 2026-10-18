#pragma once
#include "stdafx.h"
#include <string>

class CPoint
{
public:
	CPoint();
	CPoint(double x, double y);

	double GetX() const;
	double GetY() const;
	std::string ToString() const;

private:
	double m_x = 0.0;
	double m_y = 0.0;
};