#include "Game.h"

#include "Engine/Physics.h"
#include "Gameplay/Map.h"

Map* Game::s_map = nullptr;
Physics* Game::s_physics = nullptr;

Game::Game()
{
	s_map = new Map();
	s_physics = new Physics();
}

Game::~Game()
{
	delete s_map;
	delete s_physics;

	s_map = nullptr;
	s_physics = nullptr;
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
	//TODO: fixed update
	s_physics->Update(delta);

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

Physics* Game::GetPhysics()
{
	return s_physics;
}

