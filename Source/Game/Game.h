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

	void Pause();
	void Unpause();

	Map& GetMap() const;
	Physics& GetPhysics() const;

public: 
	static Game& Instance();

protected:
	Map* m_map;
	Physics* m_physics;

	bool m_isPaused = false;

protected:
	static Game* s_instance;

};
#endif

