#ifndef RESPAWN_H
#define RESPAWN_H

#include "Engine/Physics.h"
#include "Game/Actor.h"

struct Collider;

class RespawnZone : public Actor
{
	typedef Actor Base;

public:
	RespawnZone(const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~RespawnZone();

public:
	virtual void Initialise() override;
	virtual void Destroy() override;

	void HandleOnCollision(const HitInfo& hitInfo);

public:
	Collider m_collider;
};
#endif

