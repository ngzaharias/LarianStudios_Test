#include "Paddle.h"

#include "Utility/Math.h"

#include <SFML/Graphics.hpp>

#include <cmath>

Paddle::Paddle()
{
	m_sprite.setPosition(400.0f, 600.0f);
	m_sprite.setSize(sf::Vector2f(250.0f, 30.0f));
	m_sprite.setFillColor(sf::Color::White);
	m_sprite.setOrigin(m_sprite.getSize() / 2.0f);
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
	position.x = Math::Clamp(position.x, 0.0f + halfWidth, 800.0f - halfWidth);
	position.y = m_sprite.getPosition().y;

	m_sprite.setPosition(position);
}

void Paddle::Draw(sf::RenderWindow* window)
{
	Base::Draw(window);
	window->draw(m_sprite);
}

