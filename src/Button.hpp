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

	inline void setFontSize(int size) {
		drawingText.setFont(font);
		drawingText.setString(text);
		drawingText.setFillColor(sf::Color::Black);
		drawingText.setCharacterSize(size);
		sf::FloatRect texRect = drawingText.getLocalBounds();
		drawingText.setOrigin(texRect.left + texRect.width / 2.0f, texRect.top + texRect.height / 2.0f);
        drawingText.setPosition(sf::Vector2f(x + width / 2.0f, y + height / 2.0f));
	}

private:
	onClickButtonListener listener;
	bool hasFunctionListener = false;

	sf::Font font;
	sf::Text drawingText;
	sf::String text;
	unsigned int x;
	unsigned int y;
	unsigned int width;
	unsigned int height;
};
