#include "GameApplication.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

GameApplication::GameApplication()
{
}

GameApplication::~GameApplication()
{
}

bool GameApplication::Initialise(int agrc, char* argv[])
{
	m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!");

	return true;
}

void GameApplication::Destroy()
{
	delete m_window;
}

bool GameApplication::Update()
{
	return true;
}

bool GameApplication::Draw()
{
	if (m_window->isOpen() == false)
		return false;

	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window->close();
		}
	}

	m_window->clear();
	m_window->display();

	return true;
}