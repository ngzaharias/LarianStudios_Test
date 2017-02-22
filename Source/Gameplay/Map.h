#ifndef MAP_H
#define MAP_H

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

protected:
	int m_lives = 0;
	int m_score = 0;

	sf::Font m_font;
	sf::Text m_livesText;
	sf::Text m_scoreText;

	std::vector<Actor*> m_actors;
	std::vector<Actor*> m_actorsToDestroy;

};
#endif
