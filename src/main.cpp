#include <iostream>
#include <SFML/Graphics.hpp>

#include "Window.hpp"
#include "Grid.hpp"
#include "Button.hpp"

int main()
{
	Window window("Minesweeper", 100, 100);
	sf::Font arial;
    if(!arial.loadFromFile("res/arial.ttf")) {
		std::cout << "Could not open font!" << std::endl;
    }

	Grid grid(32, 32, 2, 8, 8);
	grid.setTopOffset(30);

	window.setSize(grid.getRequiredWidth(), grid.getRequiredHeight());

    Button button("Restart", 10, 5, 50, 20, arial);
	button.setFontSize(15);
    bool test = false;

    button.setOnClickButtonListener([&](sf::Event& e) {
			if(e.type == sf::Event::EventType::MouseButtonPressed) {
				test = true;
			}
    });

    button.subscribe(window);

	sf::RectangleShape fill(sf::Vector2f(100, 100));
	fill.setFillColor(sf::Color::White);

	while (window.isOpen()) {
		window.update();
		window.get()->draw(fill);
		button.draw(window);
		grid.draw(window);


		window.display();

		fill.setSize(sf::Vector2f(window.width, window.height));
		if(test) {
			std::cout << "Clicked!" << std::endl;
			test = false;
		}

	}

	return 0;
}
