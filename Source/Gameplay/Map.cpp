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

	//walls
	{
		Wall* wallTop = new Wall(sf::Vector2f(400.0f, -100.0f), sf::Vector2f(800.0f, 200.0f));
		Wall* wallBottom = new Wall(sf::Vector2f(400.0f, 700.0f), sf::Vector2f(800.0f, 200.0f));
		Wall* wallLeft = new Wall(sf::Vector2f(-100.0f, 300.0f), sf::Vector2f(200.0f, 600.0f));
		Wall* wallRight = new Wall(sf::Vector2f(900.0f, 300.0f), sf::Vector2f(200.0f, 600.0f));
		m_physics->RegisterStatic(wallTop);
		m_physics->RegisterStatic(wallBottom);
		m_physics->RegisterStatic(wallLeft);
		m_physics->RegisterStatic(wallRight);
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
			m_physics->RegisterStatic(brick);
			m_actors.push_back(brick);
		}
	}

	{
		Paddle* paddle = new Paddle();
		paddle->Initialise();
		m_physics->RegisterDynamic(paddle);
		m_actors.push_back(paddle);
	}

	{
		//TODO: Implement render layers
		//HACK: done last to ensure it renders on top
		Ball* ball = new Ball();
		ball->Initialise();
		m_physics->RegisterDynamic(ball);
		m_actors.push_back(ball);
	}
}

void Map::Unload()
{
	for (size_t i = 0; i < m_actors.size(); ++i)
	{
		m_actors[i]->Destroy();
		delete m_actors[i];
	}
}

void Map::Update(sf::RenderWindow* window, float delta)
{
	m_physics->Update();

	// update objects
	for (size_t i = 0; i < m_actors.size(); ++i)
	{
		m_actors[i]->Update(window, delta);
	}
}

void Map::Draw(sf::RenderWindow* window)
{
	for (size_t i = 0; i < m_actors.size(); ++i)
	{
		m_actors[i]->Draw(window);
	}
}