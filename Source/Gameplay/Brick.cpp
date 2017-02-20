#include "Brick.h"

#include <SFML/Graphics.hpp>

Brick::Brick(sf::Vector2f position, sf::Vector2f size)
{
	m_sprite.setFillColor(sf::Color::Red);
	m_sprite.setPosition(position);
	m_sprite.setSize(size);

	m_sprite.setOrigin(m_sprite.getSize() / 2.0f);
}

Brick::~Brick()
{
}

void Brick::Initialise()
{
	Base::Initialise();
}

void Brick::Destroy()
{
	Base::Destroy();
}

void Brick::Update(sf::RenderWindow* window, float delta)
{
	Base::Update(window, delta);
	
	//TODO: 
}

void Brick::Draw(sf::RenderWindow* window)
{
	Base::Draw(window);

	window->draw(m_sprite);
}

