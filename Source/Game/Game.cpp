#include "Game.h"

#include "Gameplay/Map.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Initialise()
{
	m_map = new Map();
	m_map->Load();
}

void Game::Destroy()
{
	m_map->Unload();
	delete m_map;
}

void Game::Update(sf::RenderWindow* window, float delta)
{
	m_map->Update(window, delta);
}

void Game::Draw(sf::RenderWindow* window)
{
	m_map->Draw(window);
}


//EOF