#ifndef BRICK_H
#define BRICK_H

#include "Engine/Physics.h"
#include "Game/Actor.h"

#include <SFML/Graphics/RectangleShape.hpp>

struct Collider;

class Brick : public Actor
{
	typedef Actor Base;

public:
	Brick(sf::Vector2f position, sf::Vector2f size);
	virtual ~Brick();

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
