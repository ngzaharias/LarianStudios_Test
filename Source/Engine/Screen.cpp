#include "Screen.h"

#include <SFML/Graphics/RenderWindow.hpp>

int Screen::width = 800;
int Screen::height = 600;
sf::RenderWindow* Screen::s_window = nullptr;

sf::RenderWindow* Screen::GetWindow() 
{ 
	return s_window; 
}

void Screen::SetWindow(sf::RenderWindow* window) 
{ 
	s_window = window; 
}