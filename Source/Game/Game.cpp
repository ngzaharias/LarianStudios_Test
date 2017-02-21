#include "Game.h"

#include "Gameplay/Map.h"

Map* Game::s_map;

Game::Game()
{
	s_map = new Map();
}

Game::~Game()
{
	delete s_map;
	s_map = nullptr;
}

void Game::Initialise()
{
	s_map->Load();
}

void Game::Destroy()
{
	s_map->Unload();
}

void Game::Update(float delta)
{
	s_map->Update(delta);
}

void Game::Draw(sf::RenderWindow* window)
{
	s_map->Draw(window);
}

Map* Game::GetMap()
{
	return s_map;
}


