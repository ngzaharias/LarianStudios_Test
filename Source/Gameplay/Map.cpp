#include "Map.h"


#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "RespawnZone.h"
#include "Wall.h"

#include "Engine/Screen.h"

#include <SFML/Graphics.hpp>

Map::Map()
{
	m_actors.reserve(64);
}

Map::~Map()
{
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
		Wall* wallLeft = new Wall(sf::Vector2f(-100.0f, 300.0f), sf::Vector2f(200.0f, 600.0f));
		Wall* wallRight = new Wall(sf::Vector2f(900.0f, 300.0f), sf::Vector2f(200.0f, 600.0f));
		wallTop->Initialise();
		wallLeft->Initialise();
		wallRight->Initialise();
		m_actors.push_back(wallTop);
		m_actors.push_back(wallLeft);
		m_actors.push_back(wallRight);
	}

	// respawns
	{
		RespawnZone* respawn = new RespawnZone(sf::Vector2f(400.0f, 650.0f), sf::Vector2f(800.0f, 200.0f));
		respawn->Initialise();
		m_actors.push_back(respawn);
	}

	// TODO: Spawn Pool
	// bricks
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

	// paddles
	{
		Paddle* paddle = new Paddle();
		paddle->Initialise();
		m_actors.push_back(paddle);
	}

	// balls
	{
		//TODO: Implement render layers
		//HACK: done last to ensure it renders on top
		Ball* ball = new Ball();
		ball->Initialise();
		m_actors.push_back(ball);
	}


	m_font.loadFromFile("Assets/Fonts/kenpixel_square.ttf");

	m_lives = 3;
	m_livesText.setFont(m_font);
	m_livesText.setStyle(sf::Text::Bold);
	m_livesText.setPosition(40.0f, Screen::height - 40.0f);

	m_score = 0;
	m_scoreText.setFont(m_font);
	m_scoreText.setStyle(sf::Text::Bold);
	m_scoreText.setPosition(Screen::width - 60.0f, Screen::height - 40.0f);

	UpdateLives(0);
	UpdateScore(0);
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

	window->draw(m_livesText);
	window->draw(m_scoreText);
}

void Map::DestroyActor(Actor* actor)
{
	m_actorsToDestroy.push_back(actor);
}

void Map::UpdateLives(int value)
{
	m_lives += value;

	char buffer[10];
	_itoa_s(m_lives, buffer, 10);
	sf::String text(buffer);
	m_livesText.setString(text);
}

void Map::UpdateScore(int value)
{
	m_score += value;

	char buffer[10];
	_itoa_s(m_score, buffer, 10);
	sf::String text(buffer);
	m_scoreText.setString(text);
}

void Map::CleanupActors()
{
	std::vector<Actor*>::iterator destroy = m_actorsToDestroy.begin();
	std::vector<Actor*>::iterator destroyEnd = m_actorsToDestroy.end();
	for (; destroy != destroyEnd; ++destroy)
	{
		for (size_t i = m_actors.size() - 1; i >= 0; --i)
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
