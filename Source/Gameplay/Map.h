#ifndef MAP_H
#define MAP_H

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
	int lives = 0;
	int score = 0;

	std::vector<Actor*> m_actors;
	std::vector<Actor*> m_actorsToDestroy;

};
#endif
