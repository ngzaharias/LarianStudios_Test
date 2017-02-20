#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/System/Vector2.hpp>

namespace sf
{
	class RenderWindow;
}

class Actor
{
public:
	Actor();
	virtual ~Actor();

public:
	virtual void Initialise();
	virtual void Destroy();

	virtual void Update(sf::RenderWindow* window, float delta);
	virtual void Draw(sf::RenderWindow* window);

protected:

};
#endif
//EOF