#include "Map.h"

#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "Wall.h"

#include <SFML/Graphics.hpp>

Map::Map()
{
	m_physics = new Physics();
	m_actors.reserve(64);
}

Map::~Map()
{
	delete m_physics;
}

void Map::Load()
{
	//TODO: 
	// - settings
	// - load from file
	// - actor factory?

	//walls
	{
		Wall* wallTop = new Wall(sf::Vector2f(400.0f, -100.0f), sf::Vector2f(800.0f, 200.0f));
		Wall* wallBottom = new Wall(sf::Vector2f(400.0f, 700.0f), sf::Vector2f(800.0f, 200.0f));
		Wall* wallLeft = new Wall(sf::Vector2f(-100.0f, 300.0f), sf::Vector2f(200.0f, 600.0f));
		Wall* wallRight = new Wall(sf::Vector2f(900.0f, 300.0f), sf::Vector2f(200.0f, 600.0f));
		m_actors.push_back(wallTop);
		m_actors.push_back(wallBottom);
		m_actors.push_back(wallLeft);
		m_actors.push_back(wallRight);
	}

	// TODO: Spawn Pool
	sf::Vector2f brickSize = sf::Vector2f(90, 40);
	for (int y = 1; y < 6; ++y)
	{
		for (int x = 1; x < 8; ++x)
		{
			sf::Vector2f position = sf::Vector2f(x * 100.0f, y * 50.0f);
			Brick* brick = new Brick(position, brickSize);
			brick->Initialise();
			m_actors.push_back(brick);
		}
	}

	{
		Paddle* paddle = new Paddle();
		paddle->Initialise();
		m_actors.push_back(paddle);
	}

	{
		//TODO: Implement render layers
		//HACK: done last to ensure it renders on top
		Ball* ball = new Ball();
		ball->Initialise();
		m_actors.push_back(ball);
	}
}

void Map::Unload()
{
	std::vector<Actor*>::iterator itr = m_actors.begin();
	std::vector<Actor*>::iterator end = m_actors.end();
	for (; itr != end; ++itr)
	{
		Actor* actor = (*itr);
		if (actor != nullptr)
		{
			actor->Destroy();
			delete actor;
		}
	}
}

void Map::Update(float delta)
{
	//TODO: fixed update
	// physics first
	m_physics->Update();

	std::vector<Actor*>::iterator itr = m_actors.begin();
	std::vector<Actor*>::iterator end = m_actors.end();
	for (; itr != end; ++itr)
	{
		Actor* actor = (*itr);
		if (actor != nullptr)
		{
			actor->Update(delta);
		}
	}

	CleanupActors();
}

void Map::Draw(sf::RenderWindow* window)
{
	std::vector<Actor*>::iterator itr = m_actors.begin();
	std::vector<Actor*>::iterator end = m_actors.end();
	for (; itr != end; ++itr)
	{
		Actor* actor = (*itr);
		if (actor != nullptr)
		{
			actor->Draw(window);
		}
	}
}

void Map::DestroyActor(Actor* actor)
{
	m_actorsToDestroy.push_back(actor);
}

Physics* Map::GetPhysics()
{
	return m_physics;
}

void Map::CleanupActors()
{
	std::vector<Actor*>::iterator destroy = m_actorsToDestroy.begin();
	std::vector<Actor*>::iterator destroyEnd = m_actorsToDestroy.end();
	for (; destroy != destroyEnd; ++destroy)
	{
		for (int i = m_actors.size() - 1; i >= 0; --i)
		{
			Actor* actor = m_actors[i];
			if ((*destroy) == actor)
			{
				m_actors.erase(m_actors.begin() + i);
				delete actor;
				break;
			}
		}
	}
	m_actorsToDestroy.clear();
}
