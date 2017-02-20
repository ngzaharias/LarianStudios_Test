#ifndef MAP_H
#define MAP_H

#include <vector>

namespace sf
{
	class RenderWindow;
}

class Actor;
class Ball;
class Brick;
class Paddle;
class Physics;

class Map
{
public:
	Map();
	~Map();

public:
	void Load();
	void Unload();

	void Update(sf::RenderWindow* window, float delta);
	void Draw(sf::RenderWindow* window);

protected:
	Physics* m_physics;
	std::vector<Actor*> m_actors;

};
#endif
//EOF