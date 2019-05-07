#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Window.hpp"
#include "Grid.hpp"
#include "Button.hpp"

const int GRID_SIZE_X = 10;
const int GRID_SIZE_Y = 10;

const int MINE_COUNT = 18;

bool gameOpened = false;

void initGame(char colors[]) {
	for(int i=0; i < GRID_SIZE_X * GRID_SIZE_Y; i++)
		colors[i] = 2;
	gameOpened = false;
}

void openGame(int x, int y, char colors[]) {

}

int main()
{
	char colors[GRID_SIZE_X * GRID_SIZE_Y];
	initGame(colors);

	Window window("Minesweeper", 100, 100);
	sf::Font arial;
    if(!arial.loadFromFile("res/arial.ttf")) {
		std::cout << "Could not open font!" << std::endl;
    }

	Grid grid(32, 32, 2, GRID_SIZE_X, GRID_SIZE_Y);
	grid.setTopOffset(30);

	window.setSize(grid.getRequiredWidth(), grid.getRequiredHeight());

    Button button("Restart", 10, 5, 50, 20, arial);
	button.setFontSize(13);

    button.setOnClickButtonListener([&](sf::Event& e) {
			if(e.type == sf::Event::EventType::MouseButtonPressed) {
				initGame(colors);
			}
    });

    button.subscribe(window);

    window.addEventListener([&](sf::Event& e) {
        if(e.type == sf::Event::EventType::MouseButtonReleased) {
			unsigned int eventX = e.mouseButton.x, eventY = e.mouseButton.y;
			if(eventY >= grid.getTopOffset()) {
				sf::Vector2i res = grid.getCellPosition(eventX, eventY);
				std::cout << res.x << " " << res.y << std::endl;
			}
		}
	});

	sf::RectangleShape fill(sf::Vector2f(100, 100));
	fill.setFillColor(sf::Color::White);

	while (window.isOpen()) {
		window.update();
		window.get()->draw(fill);
		button.draw(window);
		grid.draw(window, colors);


		window.display();

		fill.setSize(sf::Vector2f(window.width, window.height));
	}

	return 0;
}
