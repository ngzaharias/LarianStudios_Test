#ifndef WALL_H
#define WALL_H

#include "Game/Actor.h"

#include "Engine/Physics.h"

class Wall : public Actor
{
	typedef Actor Base;

public:
	Wall(const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~Wall();

public:
	virtual void Initialise() override;
	virtual void Destroy() override;

public:
	Collider m_collider;
};
#endif

