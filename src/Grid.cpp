#include "Grid.hpp"

Grid::Grid(unsigned int width, unsigned int height,
	unsigned int border, unsigned int gridXCount, unsigned int gridYCount)
	: width(width), height(height), border(border), gridXCount(gridXCount), gridYCount(gridYCount) {

	requiredWidth = border * (gridXCount + 1) + width * gridXCount;
	requiredHeight = border * (gridYCount + 1) + height * gridYCount;
}

Grid::~Grid() {

}

/*
-2 NOT OPENED
-1 MINE
 0 EMPTY
 ... // until 8
*/

void Grid::draw(Window& window, char colors[]) {
	sf::RenderWindow* context = window.get();

	sf::RectangleShape rekt;
	//select color based on color array
	rekt.setFillColor(sf::Color::Black);
	rekt.setSize(sf::Vector2f(requiredWidth, requiredHeight));
	rekt.setPosition(0, topOffset);
	context->draw(rekt);
	for(unsigned int i = 0; i <= gridXCount; i++) {
		for(unsigned int j=0; j <= gridYCount; j++) {
			switch (colors[i + j * gridXCount]) {
			case 2:
				rekt.setFillColor(sf::Color(155, 155, 155));
                break;
			case 1:
				rekt.setFillColor(sf::Color::Red);
				break;
			case 0:
				rekt.setFillColor(sf::Color::White);
				break;
			}
			rekt.setSize(sf::Vector2f(width, height));
			rekt.setPosition(border + i * border + i * width, border + topOffset + j * border + j * height);
			context->draw(rekt);
		}
	}

}

void Grid::setTopOffset(unsigned int offset) {
	requiredWidth  = border * (gridXCount + 1) + width * gridXCount;
	requiredHeight = offset + border * (gridYCount + 1) + height * gridYCount;
	topOffset = offset;
}

sf::Vector2i Grid::getCellPosition(int x, int y) {
    y -= topOffset;
	sf::Vector2i res;
	res.x = x / (border + width);
	res.y = y / (border + height);
	return res;
}
