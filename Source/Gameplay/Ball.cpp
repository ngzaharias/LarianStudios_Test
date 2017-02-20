#include "Ball.h"

#include "Brick.h"
#include "Paddle.h"

#include <SFML/Graphics.hpp>

Ball::Ball()
{
	m_sprite.setSize(sf::Vector2f(20.0f, 20.0f));
	m_sprite.setFillColor(sf::Color::Green);
	m_sprite.setOrigin(m_sprite.getSize() / 2.0f);
	m_sprite.setPosition(sf::Vector2f(400, 300));
}

Ball::~Ball()
{
}

void Ball::Initialise()
{
	Base::Initialise();

	m_velocity = sf::Vector2f(0.0f, 100.0f);
}

void Ball::Destroy()
{
	Base::Destroy();
}

void Ball::Update(sf::RenderWindow* window, float delta)
{
	Base::Update(window, delta);

	sf::Vector2f position = m_sprite.getPosition();
	m_sprite.setPosition(position + m_velocity * delta);
}

void Ball::Draw(sf::RenderWindow* window)
{
	Base::Draw(window);

	window->draw(m_sprite);
}

void Ball::HandleOnCollision()
{
	//TODO: bounce ball with reflect
	m_velocity *= -1.0f;
}

