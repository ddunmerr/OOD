#include "CCanvas.h"
#include "CShapeController.h"
#include "CShapeDrawer.h"
#include "CShapeParser.h"
#include "consts.h"
#include <iostream>
#include <memory>
#include <vector>

int main()
{
	CShapeController controller(std::cin, std::cout);
	controller.Run();

	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Shapes");
	CCanvas canvas(window);

	while (window.isOpen())
	{
		while (auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear(sf::Color(240, 240, 240));
		CShapeDrawer::DrawAll(controller.GetShapes(), canvas);
		window.display();
	}

	return 0;
}
