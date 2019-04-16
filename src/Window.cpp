#include "Window.hpp"

Window::Window(sf::String title, unsigned int width, unsigned int height) {
	m_Window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	this->title = title;
	this->width = width;
	this->height = height;
}

Window::~Window() {
	delete m_Window;
}

void Window::setSize(unsigned int width, unsigned int height) {
	m_Window->create(sf::VideoMode(width, height), title);
	this->width = width;
	this->height = height;
}

void Window::update() {
	m_Window->clear();

	sf::Event event;
	while(m_Window->pollEvent(event)) {

		for(unsigned int i = 0; i < m_listeners.size(); i++) {
			m_listeners[i](event);
		}

		if(event.type == sf::Event::Closed)
			m_Window->close();
	}
}

void Window::display() {
	m_Window->display();
}
