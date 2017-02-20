#ifndef WALL_H
#define WALL_H

#include "Game/Actor.h"

#include <SFML/Graphics/RectangleShape.hpp>

class Wall : public Actor
{
	typedef Actor Base;

public:
	Wall(const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~Wall();

public:
	virtual void Initialise() override;
	virtual void Destroy() override;

	virtual void Update(sf::RenderWindow* window, float delta) override;
	virtual void Draw(sf::RenderWindow* window) override;

	virtual void HandleOnCollision(const HitInfo& hitInfo) override;

public:

};
#endif
//EOF