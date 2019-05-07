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
 0 NOT OPENED
 1 EMPTY
 2 MINE
 3 FLAG
*/

void Grid::draw(Window& window, char colors[], char mines[], sf::Font font) {
	sf::RenderWindow* context = window.get();

	sf::RectangleShape rekt;
	//select color based on color array
	rekt.setFillColor(sf::Color::Black);
	rekt.setSize(sf::Vector2f(requiredWidth, requiredHeight));
	rekt.setPosition(0, topOffset);
	context->draw(rekt);
	for(unsigned int i = 0; i <= gridXCount; i++) {
		for(unsigned int j=0; j <= gridYCount; j++) {
			sf::Text drawingText;
			bool hasText = false;
			sf::FloatRect texRect;
			int drawX = border + i * border + i * width;
			int drawY = border + topOffset + j * border + j * height;
			switch (colors[i + j * gridXCount]) {
			case 0:
				rekt.setFillColor(sf::Color(155, 155, 155));
                break;
			case 1:
				rekt.setFillColor(sf::Color::White);
				// draw number here if it should be here
				if(mines[i + j * gridXCount] != 0){
					drawingText.setFont(font);
					drawingText.setString(sf::String((char)('0' + mines[i + j * gridXCount])));
					drawingText.setFillColor(sf::Color(65 * mines[i + j * gridXCount], 45 * mines[i + j * gridXCount], 86 * mines[i + j * gridXCount]));
					drawingText.setCharacterSize(std::min(width, height));
					texRect = drawingText.getLocalBounds();
					drawingText.setOrigin(texRect.left + texRect.width / 2.0f, texRect.top + texRect.height / 2.0f);
					drawingText.setPosition(sf::Vector2f(drawX + width / 2.0f, drawY + height / 2.0f));
					hasText = true;
				}
				break;
			case 2:
				rekt.setFillColor(sf::Color::Red);
				break;
			case 3:
				rekt.setFillColor(sf::Color::Blue);
				break;
			}
			rekt.setSize(sf::Vector2f(width, height));
			rekt.setPosition(drawX, drawY);
			context->draw(rekt);
			if(hasText)
				context->draw(drawingText);
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
