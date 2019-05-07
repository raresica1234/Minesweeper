#pragma once

#include <iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

#include "Window.hpp"

using onClickButtonListener = std::function<void(sf::Event& e)>;

class Button {
public:
	Button(sf::String text, unsigned int x, unsigned int y, unsigned int width, unsigned int height, sf::Font font);
	~Button();

	void draw(Window& window);

    void subscribe(Window& window);

	inline void setOnClickButtonListener(onClickButtonListener listener) {
        this->listener = listener;
        hasFunctionListener = true;
	}


private:
	onClickButtonListener listener;
	bool hasFunctionListener = false;

	sf::Font font;

	sf::String text;
	unsigned int x;
	unsigned int y;
	unsigned int width;
	unsigned int height;
};
