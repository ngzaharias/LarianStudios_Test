#ifndef BALL_H
#define BALL_H

#include "Game/Actor.h"

#include <SFML/Graphics/RectangleShape.hpp>

class Ball : public Actor
{
	typedef Actor Base;

public:
	Ball();
	virtual ~Ball();

public:
	virtual void Initialise() override;
	virtual void Destroy() override;

	virtual void Update(sf::RenderWindow* window, float delta) override;
	virtual void Draw(sf::RenderWindow* window) override;

	virtual void HandleOnCollision(const HitInfo& hitInfo) override;

public:
	sf::RectangleShape m_sprite;
	sf::Vector2f m_velocity;
};
#endif
//EOF