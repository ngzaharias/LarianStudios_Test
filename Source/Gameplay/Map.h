#ifndef MAP_H
#define MAP_H

#include "Settings/BallSettings.h"
#include "Settings/BrickSettings.h"
#include "Settings/MapSettings.h"
#include "Settings/PaddleSettings.h"

#include <rapidjson/document.h>
#include <SFML/Graphics/Text.hpp>

#include <vector>

namespace sf
{
	class RenderWindow;
}

class Actor;

class Map
{
public:
	Map();
	~Map();

public:
	void Initialise();
	void Destroy();

	void Update(float delta);
	void Draw(sf::RenderWindow* window);

	void Load();
	void Unload();
	void Reload();

	void DestroyActor(Actor* actor);

	void UpdateLives(int value);
	void UpdateScore(int value);

private:
	void LoadSettings(const rapidjson::Value& value);
	void LoadBallSettings(const rapidjson::Value& value);
	void LoadBrickSettings(const rapidjson::Value& value);
	void LoadMapSettings(const rapidjson::Value& value);
	void LoadPaddleSettings(const rapidjson::Value& value);

	void CleanupActors();

protected:
	BallSettings m_ballSettings;
	std::vector<BrickSettings> m_brickSettings;
	MapSettings m_mapSettings;
	PaddleSettings m_paddleSettings;

	std::vector<Actor*> m_actors;
	std::vector<Actor*> m_actorsToDestroy;

	sf::Font m_font;
	sf::Text m_infoText;
	sf::Text m_livesText;
	sf::Text m_scoreText;
	
	int m_lives = 0;
	int m_score = 0;

};
#endif
