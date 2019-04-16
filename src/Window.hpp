#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

typedef void (*EventListener)(sf::Event&);

class Window {
public:
	Window(sf::String title, unsigned int width, unsigned int height);
	~Window();

	inline bool isOpen() { return m_Window->isOpen(); }
	inline sf::RenderWindow* get() { return m_Window; }

	void setSize(unsigned int width, unsigned int height);

	void update();

	void display();

	int addEventListener(EventListener listener);

public:
	sf::String title;
	int width, height;

private:
	sf::RenderWindow* m_Window;

	std::vector<EventListener> m_listeners;
};
