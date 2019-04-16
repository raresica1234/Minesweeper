#include <SFML/Graphics.hpp>

#include "Window.hpp"
#include "Grid.hpp"

int main()
{
	Window window("Minesweeper", 100, 100);

	Grid grid(32, 32, 2, 8, 8);

	window.setSize(grid.getRequiredWidth(), grid.getRequiredHeight());

	sf::RectangleShape fill(sf::Vector2f(100, 100));
	fill.setFillColor(sf::Color::White);

	while (window.isOpen()) {
		window.update();
		window.get()->draw(fill);
		grid.draw(window);

		window.display();

		fill.setSize(sf::Vector2f(window.width, window.height));
	}

	return 0;
}
