#ifndef PADDLE_H
#define PADDLE_H

#include "Game/Actor.h"
#include "Engine/Physics.h"
#include "Settings/PaddleSettings.h"

#include <SFML/Graphics/RectangleShape.hpp>

class Paddle : public Actor
{
	typedef Actor Base;

public:
	Paddle(const PaddleSettings& settings);
	virtual ~Paddle();

public:
	virtual void Initialise() override;
	virtual void Destroy() override;

	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow* window) override;

	void HandleOnCollision(const HitInfo& hitInfo);

private:

	void SyncColliders();

	void Debug_DrawColliders(sf::RenderWindow* window);

public:
	sf::RectangleShape m_sprite = sf::RectangleShape();
	Collider m_collider;

};
#endif

