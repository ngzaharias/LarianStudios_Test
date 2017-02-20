#ifndef BRICK_H
#define BRICK_H

#include "Game/Actor.h"

#include <SFML/Graphics/RectangleShape.hpp>

class Brick : Actor
{
	typedef Actor Base;

public:
	Brick(sf::Vector2f position, sf::Vector2f size);
	virtual ~Brick();

public:
	virtual void Initialise() override;
	virtual void Destroy() override;

	virtual void Update(sf::RenderWindow* window, float delta) override;
	virtual void Draw(sf::RenderWindow* window) override;

public:
	sf::RectangleShape m_sprite = sf::RectangleShape();

};
#endif
//EOF