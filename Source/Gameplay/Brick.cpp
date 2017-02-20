#include "Brick.h"

#include <SFML/Graphics.hpp>

Brick::Brick(sf::Vector2f position, sf::Vector2f size)
{
	m_position = position;

	m_sprite.setFillColor(sf::Color::Red);
	m_sprite.setPosition(m_position);
	m_sprite.setSize(size);

	m_sprite.setOrigin(m_sprite.getSize() / 2.0f);

	m_collider.width = m_sprite.getSize().x;
	m_collider.height = m_sprite.getSize().y;
	m_collider.left = m_position.x - m_sprite.getOrigin().x;
	m_collider.top = m_position.y - m_sprite.getOrigin().y;
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
	
	// static, don't need to update
	//m_collider.left = m_position.x - m_sprite.getOrigin().x;
	//m_collider.top = m_position.y - m_sprite.getOrigin().y;
}

void Brick::Draw(sf::RenderWindow* window)
{
	Base::Draw(window);

	m_sprite.setPosition(m_position);
	window->draw(m_sprite);
}

