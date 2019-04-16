#include <SFML/Graphics.hpp>

#include "Window.hpp"

int main()
{
	Window window("Minesweeper", 100, 100);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen()) {
		window.update();

		window.display();
	}

	return 0;
}
