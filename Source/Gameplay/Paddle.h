#ifndef PADDLE_H
#define PADDLE_H

#include "Game/Actor.h"

#include <SFML/Graphics/RectangleShape.hpp>

class Paddle : public Actor
{
	typedef Actor Base;

public:
	Paddle();
	virtual ~Paddle();

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