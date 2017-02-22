#include "Map.h"

#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "RespawnZone.h"
#include "Wall.h"
#include "Engine/Screen.h"
#include "Game/Game.h"
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

void Map::Initialise()
{
	rapidjson::Document document;
	if (JsonHelper::LoadDocument("Assets/Settings/Maps/BasicMap.json", document) == true)
	{
		LoadSettings(document);
	}

	m_font.loadFromFile(m_mapSettings.fontpath);

	m_infoText.setFont(m_font);
	m_infoText.setCharacterSize(20);
	m_infoText.setPosition(Screen::width / 2.0f - 80.0f, Screen::height - 40.0f);
	m_infoText.setString("ESC TO RELOAD");
	m_infoText.setStyle(sf::Text::Bold);

	m_livesText.setFont(m_font);
	m_livesText.setPosition(40.0f, Screen::height - 40.0f);
	m_livesText.setStyle(sf::Text::Bold);

	m_scoreText.setFont(m_font);
	m_scoreText.setPosition(Screen::width - 60.0f, Screen::height - 40.0f);
	m_scoreText.setStyle(sf::Text::Bold);

	Load();
}

void Map::Destroy()
{
	Unload();
}

void Map::Update(float delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == true)
	{
		Reload();
		Game::Instance().Unpause();
	}

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

	window->draw(m_infoText);
	window->draw(m_livesText);
	window->draw(m_scoreText);
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

	// bricks
	{
		std::vector<BrickSettings>::iterator brickItr = m_brickSettings.begin();
		std::vector<BrickSettings>::iterator brickEnd = m_brickSettings.end();
		for (; brickItr != brickEnd; ++brickItr)
		{
			Brick* brick = new Brick(*brickItr);
			brick->Initialise();
			m_actors.push_back(brick);
		}
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

	// map
	{

		
		m_lives = m_mapSettings.lives;
		m_score = m_mapSettings.score;

		//HACK:
		UpdateLives(0);
		UpdateScore(0);
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
	m_actors.clear();
}

void Map::Reload()
{
	Unload();
	Load();
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

	if (m_lives <= 0)
	{
		Game::Instance().Pause();
	}
}

void Map::UpdateScore(int value)
{
	m_score += value;

	char buffer[10];
	_itoa_s(m_score, buffer, 10);
	sf::String text(buffer);
	m_scoreText.setString(text);
}

void Map::LoadSettings(const rapidjson::Value& value)
{
	LoadBallSettings(value);
	LoadBrickSettings(value);
	LoadMapSettings(value);
	LoadPaddleSettings(value);
}

void Map::LoadBallSettings(const rapidjson::Value& value)
{
	const char* member = "balls";
	if (value.HasMember(member) == true && value[member].IsString() == true)
	{
		rapidjson::Document settings;
		const char* filepath = value[member].GetString();
		if (JsonHelper::LoadDocument(filepath, settings) == true)
		{
			m_ballSettings.Parse(settings);
		}
	}
}

void Map::LoadBrickSettings(const rapidjson::Value& value)
{
	const char* member = "bricks";
	if (value.HasMember(member) == true && value[member].IsString() == true)
	{
		rapidjson::Document settings;
		const char* filepath = value[member].GetString();
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
}

void Map::LoadMapSettings(const rapidjson::Value& value)
{
	// map settings
	m_mapSettings.Parse(value);
}

void Map::LoadPaddleSettings(const rapidjson::Value& value)
{
	const char* member = "paddles";
	if (value.HasMember(member) == true && value[member].IsString() == true)
	{
		rapidjson::Document settings;
		const char* filepath = value[member].GetString();
		if (JsonHelper::LoadDocument(filepath, settings) == true)
		{
			m_paddleSettings.Parse(settings);
		}
	}
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
