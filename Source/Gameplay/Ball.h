#ifndef BALL_H
#define BALL_H

#include "Engine/Physics.h"
#include "Game/Actor.h"

#include <SFML/Graphics/RectangleShape.hpp>

struct Collider;

class Ball : public Actor
{
	typedef Actor Base;

public:
	Ball();
	virtual ~Ball();

public:
	virtual void Initialise() override;
	virtual void Destroy() override;

	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow* window) override;

	virtual sf::Vector2f GetPosition() const override;

	void HandleOnCollision(const HitInfo& hitInfo);

protected:
	sf::RectangleShape m_sprite;
	Collider* m_collider = nullptr;
	Rigidbody* m_rigidbody = nullptr;
};
#endif

