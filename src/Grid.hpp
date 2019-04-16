#include <SFML/Graphics.hpp>
#include "Window.hpp"

class Grid {
public:
	Grid(unsigned int width, unsigned int height,
	 unsigned int border, unsigned int gridXCount, unsigned int gridYCount);
	~Grid();

	void draw(Window& window);

	inline int getRequiredWidth(){ return requiredWidth; }
	inline int getRequiredHeight(){ return requiredHeight; }

private:
	unsigned int width;
	unsigned int height;
	unsigned int border;
	unsigned int gridXCount;
	unsigned int gridYCount;

	unsigned int requiredWidth;
	unsigned int requiredHeight;
};
