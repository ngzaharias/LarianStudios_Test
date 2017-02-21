#ifndef RESPAWN_H
#define RESPAWN_H

#include "Game/Actor.h"

struct Collider;

class Respawn : public Actor
{
	typedef Actor Base;

public:
	Respawn(const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~Respawn();

public:
	virtual void Initialise() override;
	virtual void Destroy() override;

	//void HandleOnCollision(const HitInfo& hitInfo);

public:
	Collider* m_collider = nullptr;
};
#endif

