#pragma once

#include <SFML/Graphics.hpp>
#include "Window.hpp"

class Grid {
public:
	Grid(unsigned int width, unsigned int height,
	 unsigned int border, unsigned int gridXCount, unsigned int gridYCount);
	~Grid();

	void draw(Window& window, char colors[]);

	void setTopOffset(unsigned int offset);

	inline unsigned int getRequiredWidth() { return requiredWidth; }
	inline unsigned int getRequiredHeight() { return requiredHeight; }

	inline unsigned int getCellWidth() { return width; }
	inline unsigned int getCellHeight() { return height; }
	inline unsigned int getTopOffset() { return topOffset; }

	sf::Vector2i getCellPosition(int x, int y);

private:
	unsigned int width;
	unsigned int height;
	unsigned int border;
	unsigned int gridXCount;
	unsigned int gridYCount;

	unsigned int requiredWidth;
	unsigned int requiredHeight;

	unsigned int topOffset = 0;
};
