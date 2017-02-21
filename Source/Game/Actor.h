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
	Actor() { }
	virtual ~Actor() { }

public:
	virtual void Initialise() { }
	virtual void Destroy() { }

	virtual void Update(float delta) { }
	virtual void Draw(sf::RenderWindow* window) { }

protected:
	sf::Vector2f m_position;

};
#endif
