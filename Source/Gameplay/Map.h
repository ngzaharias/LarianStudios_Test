#ifndef MAP_H
#define MAP_H

#include <vector>

namespace sf
{
	class RenderWindow;
}

class Ball;
class Brick;
class Paddle;

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

	void CheckCollision(Ball* ball, Brick* brick);
	void CheckCollision(Ball* ball, Paddle* paddle);

protected:
	Paddle* m_paddle;
	Ball* m_ball;
	std::vector<Brick*> m_bricks;

};
#endif
//EOF