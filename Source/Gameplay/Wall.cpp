#include "Wall.h"

#include "Brick.h"
#include "Paddle.h"
#include "Engine/Physics.h"

#include <SFML/Graphics.hpp>

Wall::Wall(const sf::Vector2f& position, const sf::Vector2f& size)
{
	m_position = position;

	m_collider.width = size.x;
	m_collider.height = size.y;
	m_collider.left = m_position.x - size.x / 2;
	m_collider.top = m_position.y - size.y / 2;
}

Wall::~Wall()
{
}

void Wall::Initialise()
{
	Base::Initialise();
}

void Wall::Destroy()
{
	Base::Destroy();
}

void Wall::Update(sf::RenderWindow* window, float delta)
{
	Base::Update(window, delta);

	// static
	//m_collider.left = m_position.x - m_sprite.getOrigin().x;
	//m_collider.top = m_position.y - m_sprite.getOrigin().y;
}

void Wall::Draw(sf::RenderWindow* window)
{
	Base::Draw(window);
}

void Wall::HandleOnCollision(const HitInfo& hitInfo)
{
}

