#include "Wall.h"

#include "Engine/Physics.h"
#include "Game/Game.h"
#include "Gameplay/Map.h"

#include <SFML/Graphics.hpp>

Wall::Wall(const sf::Vector2f& position, const sf::Vector2f& size)
{
	m_position = position;

	m_collider = &Game::GetMap()->GetPhysics()->CreateCollider();
	m_collider->rectangle.width = size.x;
	m_collider->rectangle.height = size.y;
	m_collider->rectangle.left = m_position.x - size.x / 2;
	m_collider->rectangle.top = m_position.y - size.y / 2;
}

Wall::~Wall()
{
	Game::GetMap()->GetPhysics()->DestroyCollider(*m_collider);
}

void Wall::Initialise()
{
	Base::Initialise();
}

void Wall::Destroy()
{
	Base::Destroy();
}

