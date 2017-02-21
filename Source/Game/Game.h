#ifndef GAME_H
#define GAME_H

namespace sf
{
	class RenderWindow;
}

class Map;
class Physics;

class Game
{
public:
	Game();
	virtual ~Game();

public:
	virtual void Initialise();
	virtual void Destroy();

	virtual void Update(float delta);
	virtual void Draw(sf::RenderWindow* window);

public: 
	static Map* GetMap();
	static Physics* GetPhysics();

protected:

	static Map* s_map;
	static Physics* s_physics;
};
#endif

