#include "Ball.h"

#include "Brick.h"
#include "Paddle.h"
#include "Engine/Physics.h"
#include "Utility/Random.h"

#include <SFML/Graphics.hpp>

Ball::Ball()
{
	//TODO: settings
	m_position = sf::Vector2f(400.0f, 300.0f);

	m_sprite.setFillColor(sf::Color::Green);
	m_sprite.setPosition(m_position);
	m_sprite.setSize(sf::Vector2f(20.0f, 20.0f));

	m_sprite.setOrigin(m_sprite.getSize() / 2.0f);

	m_collider.width = m_sprite.getSize().x;
	m_collider.height = m_sprite.getSize().y;
	m_collider.left = m_position.x - m_sprite.getOrigin().x;
	m_collider.top = m_position.y - m_sprite.getOrigin().y;
}

Ball::~Ball()
{
}

void Ball::Initialise()
{
	Base::Initialise();

	float x = Random::Range(-300.0f, 300.0f);
	float y = Random::Range(-300.0f, 300.0f);
	m_velocity = sf::Vector2f(x, y);
}

void Ball::Destroy()
{
	Base::Destroy();
}

void Ball::Update(sf::RenderWindow* window, float delta)
{
	Base::Update(window, delta);

	m_position += m_velocity * delta;

	//TODO: have the physics sync only when required?
	// sync the collider after we move
	m_collider.left = m_position.x - m_sprite.getOrigin().x;
	m_collider.top = m_position.y - m_sprite.getOrigin().y;
}

void Ball::Draw(sf::RenderWindow* window)
{
	Base::Draw(window);

	m_sprite.setPosition(m_position);
	window->draw(m_sprite);
}

void Ball::HandleOnCollision(const HitInfo& hitInfo)
{
	//TODO: bounce ball with reflect

	float x = Random::Range(-300.0f, 300.0f);
	float y = Random::Range(-300.0f, 300.0f);
	m_velocity = sf::Vector2f(x, y);
}

