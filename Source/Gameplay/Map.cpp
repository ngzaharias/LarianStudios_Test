#include "Map.h"

#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "RespawnZone.h"
#include "Wall.h"
#include "Engine/Screen.h"
#include "Utility/JsonHelper.h"

#include <rapidjson/document.h>

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
	//TODO: actor factory?

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

	rapidjson::Document document;
	if (JsonHelper::LoadDocument("Assets/Settings/Maps/BasicMap.json", document) == true)
	{
		LoadSettings(document);

		// bricks
		std::vector<BrickSettings>::iterator brickItr = m_brickSettings.begin();
		std::vector<BrickSettings>::iterator brickEnd = m_brickSettings.end();
		for (; brickItr != brickEnd; ++brickItr)
		{
			Brick* brick = new Brick(*brickItr);
			brick->Initialise();
			m_actors.push_back(brick);
		}

		// paddles
		{
			Paddle* paddle = new Paddle(m_paddleSettings);
			paddle->Initialise();
			m_actors.push_back(paddle);
		}

		// balls
		{
			//TODO: Implement render layers
			//HACK: done last to ensure it renders on top
			Ball* ball = new Ball(m_ballSettings);
			ball->Initialise();
			m_actors.push_back(ball);
		}
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

void Map::LoadSettings(const rapidjson::Document& document)
{
	// balls
	const char* member = "balls";
	if (document.HasMember(member) == true && document[member].IsString() == true)
	{
		rapidjson::Document settings;
		const char* filepath = document[member].GetString();
		if (JsonHelper::LoadDocument(filepath, settings) == true)
		{
			m_ballSettings.Parse(settings);
		}
	}

	// bricks
	member = "bricks";
	if (document.HasMember(member) == true && document[member].IsString() == true)
	{
		rapidjson::Document settings;
		const char* filepath = document[member].GetString();
		if (JsonHelper::LoadDocument(filepath, settings) == true)
		{
			if (settings.HasMember(member) == true)
			{
				const rapidjson::Value& objectArray = settings[member];
				if (objectArray.IsArray() == true)
				{
					m_brickSettings.clear();
					for (rapidjson::SizeType i = 0; i < objectArray.Size(); ++i)
					{
						BrickSettings brickSetting;
						brickSetting.Parse(objectArray[i]);
						m_brickSettings.push_back(brickSetting);
					}
				}
			}
		}
	}

	// paddles
	member = "paddles";
	if (document.HasMember(member) == true && document[member].IsString() == true)
	{
		rapidjson::Document settings;
		const char* filepath = document[member].GetString();
		if (JsonHelper::LoadDocument(filepath, settings) == true)
		{
			m_paddleSettings.Parse(settings);
		}
	}

	// map settings
	const char* fontpath = JsonHelper::ParseString(document, "font", "Assets/Fonts/kenpixel_square.ttf");
	m_font.loadFromFile(fontpath);

	m_lives = JsonHelper::ParseInt(document, "lives", 3);
	m_livesText.setFont(m_font);
	m_livesText.setStyle(sf::Text::Bold);
	m_livesText.setPosition(40.0f, Screen::height - 40.0f);

	m_score = JsonHelper::ParseInt(document, "score", 0);
	m_scoreText.setFont(m_font);
	m_scoreText.setStyle(sf::Text::Bold);
	m_scoreText.setPosition(Screen::width - 60.0f, Screen::height - 40.0f);

	//HACK:
	UpdateLives(0);
	UpdateScore(0);
}
