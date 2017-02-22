#ifndef MAP_H
#define MAP_H

#include "Settings/BallSettings.h"
#include "Settings/BrickSettings.h"
#include "Settings/PaddleSettings.h"
//#include "Settings/WallSettings.h"

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
	void Load();
	void Unload();

	void Update(float delta);
	void Draw(sf::RenderWindow* window);

	void DestroyActor(Actor* actor);

	void UpdateLives(int value);
	void UpdateScore(int value);

private:
	void CleanupActors();
	void LoadSettings(const rapidjson::Document& document);

protected:
	int m_lives = 0;
	int m_score = 0;

	BallSettings m_ballSettings;
	std::vector<BrickSettings> m_brickSettings;
	PaddleSettings m_paddleSettings;
	//std::vector<WallSettings> m_wallSettings;

	sf::Font m_font;
	sf::Text m_livesText;
	sf::Text m_scoreText;

	std::vector<Actor*> m_actors;
	std::vector<Actor*> m_actorsToDestroy;

};
#endif
