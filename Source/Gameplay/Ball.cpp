#include "Ball.h"

#include "Game/Game.h"
#include "Gameplay/Map.h"
#include "Engine/Physics.h"
#include "Utility/Random.h"
#include "Utility/VectorHelper.h"

#include <SFML/Graphics.hpp>

Ball::Ball()
{
	//TODO: settings
	m_position = sf::Vector2f(400.0f, 300.0f);

	m_sprite.setFillColor(sf::Color::Green);
	m_sprite.setPosition(m_position);
	m_sprite.setSize(sf::Vector2f(20.0f, 20.0f));

	m_sprite.setOrigin(m_sprite.getSize() / 2.0f);

	m_collider = &Game::GetMap()->GetPhysics()->CreateCollider();
	m_collider->rectangle.width = m_sprite.getSize().x;
	m_collider->rectangle.height = m_sprite.getSize().y;
	m_collider->rectangle.left = m_position.x - m_sprite.getOrigin().x;
	m_collider->rectangle.top = m_position.y - m_sprite.getOrigin().y;

	m_rigidbody = &Game::GetMap()->GetPhysics()->CreateRigidbody(*m_collider);
}

Ball::~Ball()
{
	Game::GetMap()->GetPhysics()->DestroyCollider(*m_collider);
	Game::GetMap()->GetPhysics()->DestroyRigidbody(*m_rigidbody);
}

void Ball::Initialise()
{
	Base::Initialise();

	m_collider->callback = std::bind(&Ball::HandleOnCollision, this, std::placeholders::_1);

	float x = Random::Range(-300.0f, 300.0f);
	float y = Random::Range(-300.0f, 300.0f);
	m_rigidbody->velocity = sf::Vector2f(x, y);
}

void Ball::Destroy()
{
	Base::Destroy();
}

void Ball::Update(float delta)
{
	Base::Update(delta);

	m_position += m_rigidbody->velocity * delta;

	//TODO: have the physics sync only when required?
	// sync collider
	m_collider->rectangle.left = m_position.x - m_sprite.getOrigin().x;
	m_collider->rectangle.top = m_position.y - m_sprite.getOrigin().y;
}

void Ball::Draw(sf::RenderWindow* window)
{
	Base::Draw(window);

	// sync sprite
	m_sprite.setPosition(m_position);
	window->draw(m_sprite);
}

void Ball::HandleOnCollision(const HitInfo& hitInfo)
{
	//TODO: bounce ball with reflect
	// temp
	float magnitude = VectorHelper::Magnitude(m_rigidbody->velocity);
	sf::Vector2f direction = sf::Vector2f(Random::Range(-1, 1), Random::Range(-1, 1));
	sf::Vector2f velocity = VectorHelper::Normalize(direction) * magnitude;
	m_rigidbody->velocity = velocity;
}

