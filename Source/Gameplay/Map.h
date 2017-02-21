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

private:
	void CleanupActors();

protected:
	std::vector<Actor*> m_actors;
	std::vector<Actor*> m_actorsToDestroy;

};
#endif
