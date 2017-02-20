#include "Map.h"

#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"

#include <SFML/Graphics.hpp>

Map::Map()
{
	m_paddle = new Paddle();
	m_ball = new Ball();

	// TODO: Spawn Pool
	sf::Vector2f brickSize = sf::Vector2f(90, 40);
	for (int y = 1; y < 6; ++y)
	{
		for (int x = 1; x < 8; ++x)
		{
			sf::Vector2f position = sf::Vector2f(x * 100.0f, y * 50.0f);
			Brick* brick = new Brick(position, brickSize);
			m_bricks.push_back(brick);
		}
	}
}

Map::~Map()
{
	delete m_paddle;
	delete m_ball;

	for (size_t i = 0; i < m_bricks.size(); ++i)
	{
		delete m_bricks[i];
	}
	m_bricks.clear();
}

void Map::Load()
{
	//TODO: Load from file

	m_paddle->Initialise();
	m_ball->Initialise();

	for (size_t i = 0; i < m_bricks.size(); ++i)
	{
		Brick* brick = m_bricks[i];
		if (brick != nullptr)
		{
			m_bricks[i]->Initialise();
		}
	}
}

void Map::Unload()
{
	m_paddle->Destroy();
	m_ball->Destroy();

	for (size_t i = 0; i < m_bricks.size(); ++i)
	{
		Brick* brick = m_bricks[i];
		if (brick != nullptr)
		{
			m_bricks[i]->Destroy();
		}
	}
}

void Map::Update(sf::RenderWindow* window, float delta)
{
	//TODO:
	// - change to collision components
	// - move to a fixed update

	// collision
	CheckCollision(m_ball, m_paddle);
	for (size_t i = 0; i < m_bricks.size(); ++i)
	{
		CheckCollision(m_ball, m_bricks[i]);
	}

	// update objects
	m_paddle->Update(window, delta);
	m_ball->Update(window, delta);

	for (size_t i = 0; i < m_bricks.size(); ++i)
	{
		Brick* brick = m_bricks[i];
		if (brick != nullptr)
		{
			brick->Update(window, delta);
		}
	}
}

void Map::Draw(sf::RenderWindow* window)
{
	for (size_t i = 0; i < m_bricks.size(); ++i)
	{
		Brick* brick = m_bricks[i];
		if (brick != nullptr)
		{
			brick->Draw(window);
		}
	}

	m_paddle->Draw(window);
	m_ball->Draw(window);
}

void Map::CheckCollision(Ball* ball, Brick* brick)
{
	//AABB first
	sf::FloatRect brickRect = brick->m_sprite.getGlobalBounds();
	sf::FloatRect ballRect = ball->m_sprite.getGlobalBounds();
	if (ballRect.intersects(brickRect) == false)
		return;

	//TODO: destroy the brick

	ball->HandleOnCollision();
}

void Map::CheckCollision(Ball* ball, Paddle* paddle)
{
	//AABB first
	sf::FloatRect paddleRect = paddle->m_sprite.getGlobalBounds();
	sf::FloatRect ballRect = ball->m_sprite.getGlobalBounds();

	if (ballRect.intersects(paddleRect) == false)
		return;

	ball->HandleOnCollision();
}