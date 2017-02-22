#include "Screen.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

unsigned int Screen::width = 800;
unsigned int Screen::height = 600;
sf::RenderWindow* Screen::s_window = nullptr;

sf::RenderWindow* Screen::GetWindow() 
{ 
	return s_window; 
}

void Screen::SetWindow(sf::RenderWindow* window) 
{ 
	s_window = window; 
}

sf::Vector2i Screen::AdjustToFullscreenPosition(const sf::Window& window, sf::Vector2i position)
{
	sf::Vector2f screenSize = sf::Vector2f((float)width, (float)height);
	sf::Vector2f windowSize = sf::Vector2f(window.getSize());

	sf::Vector2f adjusted = sf::Vector2f(position);
	adjusted.x *= screenSize.x / windowSize.x;
	adjusted.y *= screenSize.y / windowSize.y;

	return sf::Vector2i(adjusted);
}