#include "Grid.hpp"

Grid::Grid(unsigned int width, unsigned int height,
	unsigned int border, unsigned int gridXCount, unsigned int gridYCount)
	: width(width), height(height), border(border), gridXCount(gridXCount), gridYCount(gridYCount) {

	requiredWidth = border * (gridXCount + 1) + width * gridXCount; 
	requiredHeight = border * (gridYCount + 1) + height * gridYCount; 
}

Grid::~Grid() {

}

void Grid::draw(Window& window) {
	sf::RenderWindow* context = window.get();

	sf::RectangleShape rekt;
	rekt.setFillColor(sf::Color::Black);
	for(unsigned int i = 0; i <= gridXCount; i++) {
		rekt.setSize(sf::Vector2f(border, requiredHeight));
		rekt.setPosition(i * border + i * width, 0);
		context->draw(rekt);

		rekt.setSize(sf::Vector2f(requiredWidth, border));
		rekt.setPosition(0, i * border + i * height);
		context->draw(rekt);
	}

}