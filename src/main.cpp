#include <iostream>
#include <random>
#include <string>

#include <SFML/Graphics.hpp>

#include "Window.hpp"
#include "Grid.hpp"
#include "Button.hpp"

const int GRID_SIZE_X = 20;
const int GRID_SIZE_Y = 20;

const int MINE_COUNT = 50;
int flagCount = MINE_COUNT;

bool gameOpened = false;
bool lost = false;
bool win = false;

sf::Vector2i directions[8] = { 	{-1, -1}, {-1, 0}, {-1, 1},
								{ 0, -1},          { 0, 1},
								{ 1, -1}, { 1, 0}, { 1, 1}
};

void initGame(char colors[], char mines[]) {
	for(int i=0; i < GRID_SIZE_X * GRID_SIZE_Y; i++)
		colors[i] = mines[i] = 0;
	gameOpened = false;
	lost = win = false;
	srand(clock());
	flagCount = MINE_COUNT;
}

bool inBounds(int x, int y) {
	if(x >= 0 && x < GRID_SIZE_X && y >= 0 && y < GRID_SIZE_Y)
		return true;
	return false;
}

void generateMines(int cursorx, int cursory, char mines[]) {
	int mC = MINE_COUNT;

	while(mC != 0) {
		int x = rand() % GRID_SIZE_X;
		int y = rand() % GRID_SIZE_Y;
		if(!(cursorx == x && cursory == y)) {
			if(mines[x + y * GRID_SIZE_X] == 0) {
				mines[x + y* GRID_SIZE_X] = -1;
				mC--;
			}
		}
	}

	//check surrounding to generate numbers

	for(int i = 0; i < GRID_SIZE_X; i++)
		for(int j = 0; j < GRID_SIZE_Y; j++) {
			if(mines[i + j * GRID_SIZE_X] == -1)
				continue;

			int k = 0;
            for(int dir = 0; dir < 8; dir++) {
				sf::Vector2i current = {i, j};
				current += directions[dir];

				if(inBounds(current.x, current.y))
					if(mines[current.x + current.y * GRID_SIZE_X] == -1)
						k++;
            }
            mines[i + j * GRID_SIZE_X] = k;
		}

	gameOpened = true;
}

void openGame(int x, int y, char colors[], char mines[]) {
	if(!inBounds(x, y))
		return;
	if(mines[x + y * GRID_SIZE_X] == -1) {
		lost = true;
		return;
	} else {
        if(mines[x + y * GRID_SIZE_X] == 0 && colors[x + y * GRID_SIZE_X] == 0) {
            colors[x + y * GRID_SIZE_X] = 1;
            for(int dir = 0; dir < 8; dir++) {
				if(mines[x + directions[dir].x + (y + directions[dir].y) * GRID_SIZE_X] != -1)
					openGame(x + directions[dir].x, y + directions[dir].y, colors, mines);
            }
        }
		colors[x + y * GRID_SIZE_X] = 1;
	}

}

void lose(char colors[], char mines[]) {
	for(int i = 0; i < GRID_SIZE_X; i++) {
		for(int j = 0; j < GRID_SIZE_Y; j++) {
            if(mines[i + j * GRID_SIZE_X] == -1)
				colors[i + j * GRID_SIZE_X] = 2;
		}
	}
}

bool allFlagsOnPoint(char colors[], char mines[]) {
    if(flagCount != 0)
		return false;
	bool res = true;

	for(int i = 0; i < GRID_SIZE_X && res; i++) {
		for(int j = 0; j < GRID_SIZE_Y && res; j++) {
            if(colors[i + j * GRID_SIZE_X] == 3)
				if(mines[i + j * GRID_SIZE_X] != -1)
					res = false;
		}
	}
	return res;
}

bool allAreaUncovered(char colors[], char mines[]) {
	bool res = true;

	for(int i = 0; i < GRID_SIZE_X && res; i++) {
		for(int j = 0; j < GRID_SIZE_Y && res; j++) {
            if(colors[i + j * GRID_SIZE_X] == 0)
				if(mines[i + j * GRID_SIZE_X] != -1)
					res = false;
		}
	}
	return res;
}

void checkWin(char colors[], char mines[]) {
	if(lost) {
        lose(colors, mines);
	} else {
		if(allFlagsOnPoint(colors, mines) || allAreaUncovered(colors, mines))
			win = true;
	}
}

int main()
{
	char colors[GRID_SIZE_X * GRID_SIZE_Y];
	char mines[GRID_SIZE_X * GRID_SIZE_Y];
	initGame(colors, mines);

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
				initGame(colors, mines);
			}
    });

    button.subscribe(window);

    window.addEventListener([&](sf::Event& e) {
        if(e.type == sf::Event::EventType::MouseButtonReleased && !lost && !win) {
			unsigned int eventX = (unsigned)e.mouseButton.x, eventY = (unsigned)e.mouseButton.y;
			if(eventY >= grid.getTopOffset()) {
				sf::Vector2i res = grid.getCellPosition(eventX, eventY);
				if(e.mouseButton.button == 0) {
					if(!gameOpened)
						generateMines(res.x, res.y, mines);
					openGame(res.x, res.y, colors, mines);



				} else if(e.mouseButton.button == 1) {
					if(colors[res.x + res.y * GRID_SIZE_X] == 0) {
						if(flagCount > 0) {
							colors[res.x + res.y * GRID_SIZE_X] = 3;
							flagCount--;
							std::cout << flagCount << "\n";
						}
					}
					else if (colors[res.x + res.y * GRID_SIZE_X] == 3){
						colors[res.x + res.y * GRID_SIZE_X] = 0;
						flagCount++;
					}
				}
				checkWin(colors, mines);
			}
		}
	});

	sf::RectangleShape fill(sf::Vector2f(100, 100));
	fill.setFillColor(sf::Color::White);

	sf::Text drawingText;
	drawingText.setFont(arial);
	drawingText.setCharacterSize(100);

	sf::Text minesLeft;
	minesLeft.setFont(arial);
	minesLeft.setCharacterSize(20);
	minesLeft.setColor(sf::Color::Red);

	while (window.isOpen()) {
		window.update();
		window.get()->draw(fill);
		button.draw(window);
		grid.draw(window, colors, mines, arial);

		if(lost) {
			drawingText.setString("You lost!");
			drawingText.setColor(sf::Color::Red);
		} else if(win) {
			drawingText.setString("You win!");
			drawingText.setColor(sf::Color::Green);
		}

		if(lost) {
			drawingText.setString("You lost!");
			drawingText.setColor(sf::Color::Red);
		} else if(win) {
			drawingText.setString("You win!");
			drawingText.setColor(sf::Color::Green);
		}

		if(win || lost) {
			drawingText.setOutlineColor(sf::Color::Black);
			drawingText.setOutlineThickness(2);

			sf::FloatRect texRect = drawingText.getLocalBounds();
			drawingText.setOrigin(texRect.left + texRect.width / 2.0f, texRect.top + texRect.height / 2.0f);
			drawingText.setPosition(sf::Vector2f(grid.getRequiredWidth() / 2.0f, grid.getRequiredHeight() / 2.0f));
			window.get()->draw(drawingText);
		}
		char temp[256];
		sprintf(temp, "Mines left: %i", flagCount);

		minesLeft.setString(sf::String(temp));

		sf::FloatRect texRect = minesLeft.getLocalBounds();
		minesLeft.setOrigin(texRect.left + texRect.width / 2.0f, texRect.top + texRect.height / 2.0f);
		minesLeft.setPosition(sf::Vector2f(grid.getRequiredWidth() / 2.0f, 20));
		window.get()->draw(minesLeft);

		window.display();
		fill.setSize(sf::Vector2f(window.width, window.height));
	}

	return 0;
}
