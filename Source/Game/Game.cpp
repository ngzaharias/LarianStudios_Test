#include "Game.h"

#include "Engine/Physics.h"
#include "Gameplay/Map.h"

Game* Game::s_instance = nullptr;

Game::Game()
{
	s_instance = this;
	m_map = new Map();
	m_physics = new Physics();
}

Game::~Game()
{
	delete m_map;
	delete m_physics;

	s_instance = nullptr;
}

void Game::Initialise()
{
	m_map->Initialise();
}

void Game::Destroy()
{
	m_map->Destroy();
}

void Game::Update(float delta)
{
	if (m_isPaused == true)
	{
		delta = 0.0f;
	}

	//TODO: fixed update
	m_physics->Update(delta);

	m_map->Update(delta);
}

void Game::Draw(sf::RenderWindow* window)
{
	m_map->Draw(window);
}

void Game::Pause()
{
	m_isPaused = true;
}

void Game::Unpause()
{
	m_isPaused = false;
}

Map& Game::GetMap() const
{
	return *m_map;
}

Physics& Game::GetPhysics() const
{
	return *m_physics;
}

Game& Game::Instance()
{
	return *s_instance;
}

