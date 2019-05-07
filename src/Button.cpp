#include "Button.hpp"

Button::Button(sf::String text, unsigned int x, unsigned int y, unsigned int width, unsigned int height, sf::Font font)
	: text(text), x(x), y(y), width(width), height(height), font(font) {

    drawingText.setFont(font);
    drawingText.setString(text);
    drawingText.setFillColor(sf::Color::Black);
    drawingText.setPosition(x, y);
}

Button::~Button() {
	// TODO: unsubscribe system
}

void Button::draw(Window& window) {
    sf::RectangleShape rect;
	rect.setPosition(sf::Vector2f(x, y));
	rect.setSize(sf::Vector2f(width, height));
    rect.setFillColor(sf::Color::Cyan);
    window.get()->draw(rect);
    window.get()->draw(drawingText);
}

void Button::subscribe(Window& window) {
	window.addEventListener([this](sf::Event& e) {
        if(e.type == sf::Event::EventType::MouseButtonPressed || e.type == sf::Event::EventType::MouseButtonReleased) {
			unsigned int eventX = e.mouseButton.x;
			unsigned int eventY = e.mouseButton.y;

            if(hasFunctionListener) {
                if(eventX >= x && eventX <= x + width && eventY >= y && eventY <= y + height)
					listener(e);
            }
		}


	});
}
