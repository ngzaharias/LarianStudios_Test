#include "Paddle.h"

#include "Utility/Math.h"

#include <SFML/Graphics.hpp>

#include <cmath>

Paddle::Paddle()
{
	m_position = sf::Vector2f(400.0f, 600.0f);

	m_sprite.setFillColor(sf::Color::White);
	m_sprite.setPosition(m_position);
	m_sprite.setSize(sf::Vector2f(250.0f, 30.0f));

	m_sprite.setOrigin(m_sprite.getSize() / 2.0f);

	m_collider.width = m_sprite.getSize().x;
	m_collider.height = m_sprite.getSize().y;
	m_collider.left = m_position.x - m_sprite.getOrigin().x;
	m_collider.top = m_position.y - m_sprite.getOrigin().y;
}

Paddle::~Paddle()
{
}

void Paddle::Initialise()
{
	Base::Initialise();
}

void Paddle::Destroy()
{
	Base::Destroy();
}

void Paddle::Update(sf::RenderWindow* window, float delta)
{
	Base::Update(window, delta);

	//TODO: 
	// - limit paddle axis
	// ? limit paddle speed

	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	sf::Vector2f position = sf::Vector2f(mousePosition);
	
	float halfWidth = m_sprite.getSize().x / 2;
	m_position.x = Math::Clamp(position.x, 0.0f + halfWidth, 800.0f - halfWidth);

	m_collider.left = m_position.x - m_sprite.getOrigin().x;
	m_collider.top = m_position.y - m_sprite.getOrigin().y;
}

void Paddle::Draw(sf::RenderWindow* window)
{
	Base::Draw(window);

	m_sprite.setPosition(m_position);
	window->draw(m_sprite);
}

