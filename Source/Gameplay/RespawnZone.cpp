#include "RespawnZone.h"

#include "Engine/Physics.h"
#include "Game/Game.h"
#include "Gameplay/Ball.h"
#include "Gameplay/Map.h"

#include <SFML/Graphics.hpp>

RespawnZone::RespawnZone(const sf::Vector2f& position, const sf::Vector2f& size)
{
	m_position = position;

	Game::GetPhysics()->RegisterCollider(m_collider);
	m_collider.rectangle.width = size.x;
	m_collider.rectangle.height = size.y;
	m_collider.rectangle.left = m_position.x - size.x / 2;
	m_collider.rectangle.top = m_position.y - size.y / 2;
	m_collider.isTrigger = true;
	m_collider.actor = this;
}

RespawnZone::~RespawnZone()
{
	Game::GetPhysics()->UnregisterCollider(m_collider);
}

void RespawnZone::Initialise()
{
	Base::Initialise();

	m_collider.callback = std::bind(&RespawnZone::HandleOnCollision, this, std::placeholders::_1);
}

void RespawnZone::Destroy()
{
	Base::Destroy();
}

void RespawnZone::HandleOnCollision(const HitInfo& hitInfo)
{
	Ball* ball = dynamic_cast<Ball*>(hitInfo.colliderB->actor);
	if (ball != nullptr)
	{
		Game::GetMap()->UpdateLives(-1);
		ball->Respawn();
	}
}