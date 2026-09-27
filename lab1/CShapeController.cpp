#include "CShapeController.h"
#include <iomanip>
#include <iostream>

CShapeController::CShapeController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void CShapeController::Run()
{
	if (ReadShapes())
	{
		PrintResults();
	}
	else
	{
		m_output << ERROR_NO_SHAPES << std::endl;
	}
}

const bool CShapeController::ReadShapes()
{
	std::string line;

	while (std::getline(m_input, line))
	{
		if (line.empty())
		{
			continue;
		}

		auto shape = CShapeParser::ParseCommand(line);
		if (shape)
		{
			m_shapes.push_back(std::move(shape));
		}
		else
		{
			m_output << ERROR_UNKNOWN_COMMAND << line << std::endl;
		}
	}

	return !m_shapes.empty();
}

void CShapeController::PrintResults()
{
	m_output << std::fixed << std::setprecision(0);

	for (const auto& shape : m_shapes)
	{
		m_output << shape->ToString() << std::endl;
	}
}
