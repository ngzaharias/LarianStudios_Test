#include "GameApplication.h"
#include "Game.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

GameApplication::GameApplication()
{
	m_clock = new sf::Clock();
	m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Breakout: Nicholas Zaharias");

	m_game = new Game();
}

GameApplication::~GameApplication()
{
	delete m_game;
	delete m_window;
}

bool GameApplication::Initialise(int agrc, char* argv[])
{
	m_game->Initialise();
	return true;
}

void GameApplication::Destroy()
{
	m_game->Destroy();
}

bool GameApplication::Update()
{
	sf::Time delta = m_clock->restart();
	m_game->Update(m_window, delta.asSeconds());
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
			return false;
		}
	}

	m_window->clear();
	m_game->Draw(m_window);
	m_window->display();

	return true;
}