#pragma once
#include "stdafx.h"
#include "consts.h"
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
	double m_x = ZERO_DOUBLE;
	double m_y = ZERO_DOUBLE;
};
