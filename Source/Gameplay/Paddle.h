#ifndef PADDLE_H
#define PADDLE_H

#include "Engine/Physics.h"
#include "Game/Actor.h"

#include <SFML/Graphics/RectangleShape.hpp>

struct Collider;

class Paddle : public Actor
{
	typedef Actor Base;

public:
	Paddle();
	virtual ~Paddle();

public:
	virtual void Initialise() override;
	virtual void Destroy() override;

	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow* window) override;

	void HandleOnCollision(const HitInfo& hitInfo);

public:
	sf::RectangleShape m_sprite = sf::RectangleShape();
	Collider* m_collider = nullptr;

};
#endif

