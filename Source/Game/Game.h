#ifndef GAME_H
#define GAME_H

namespace sf
{
	class RenderWindow;
}

class Map;

class Game
{
public:
	Game();
	virtual ~Game();

public:
	virtual void Initialise();
	virtual void Destroy();

	virtual void Update(sf::RenderWindow* window, float delta);
	virtual void Draw(sf::RenderWindow* window);

protected:

	Map* m_map;
};
#endif
//EOF