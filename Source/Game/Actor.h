#ifndef ACTOR_H
#define ACTOR_H

#include "Engine/Physics.h"

#include <SFML/Graphics/Rect.hpp>
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

	virtual void Update(sf::RenderWindow* window, float delta) { }
	virtual void Draw(sf::RenderWindow* window) { }

	virtual void HandleOnCollision(const HitInfo& hitInfo) { }

public:
	static bool IsIntersecting(const Actor& a, const Actor& b);

protected:
	sf::Vector2f m_position;
	sf::FloatRect m_collider;
};
#endif
//EOF