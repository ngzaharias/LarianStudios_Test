#include "Ball.h"

#include "Engine/Physics.h"
#include "Game/Game.h"
#include "Gameplay/Map.h"
#include "Gameplay/Paddle.h"
#include "Gameplay/RespawnZone.h"
#include "Gameplay/Wall.h"
#include "Utility/Math.h"
#include "Utility/Random.h"
#include "Utility/VectorHelper.h"

#include <SFML/Graphics.hpp>

Ball::Ball()
{
	//TODO: settings file/struct
	m_sprite.setFillColor(sf::Color::Blue);
	m_sprite.setSize(sf::Vector2f(20.0f, 20.0f));

	m_sprite.setOrigin(m_sprite.getSize() / 2.0f);

	Game::GetPhysics()->RegisterCollider(m_collider);
	m_collider.rectangle.width = m_sprite.getSize().x;
	m_collider.rectangle.height = m_sprite.getSize().y;
	m_collider.actor = this;

	 Game::GetPhysics()->RegisterRigidbody(m_rigidbody);
	 m_rigidbody.collider = &m_collider;
}

Ball::~Ball()
{
	Game::GetPhysics()->UnregisterCollider(m_collider);
	Game::GetPhysics()->UnregisterRigidbody(m_rigidbody);
}

void Ball::Initialise()
{
	Base::Initialise();

	m_collider.callback = std::bind(&Ball::HandleOnCollision, this, std::placeholders::_1);

	Respawn();
}

void Ball::Destroy()
{
	Base::Destroy();
}

void Ball::Update(float delta)
{
	Base::Update(delta);
}

void Ball::Draw(sf::RenderWindow* window)
{
	Base::Draw(window);

	// sync sprite
	m_sprite.setPosition(GetPosition());
	window->draw(m_sprite);
}

sf::Vector2f Ball::GetPosition() const
{
	float x = m_rigidbody.collider->rectangle.left + m_sprite.getSize().x / 2;
	float y = m_rigidbody.collider->rectangle.top + m_sprite.getSize().y / 2;
	return sf::Vector2f(x, y);
}

void Ball::SetDirection(sf::Vector2f direction)
{
	float magnitude = VectorHelper::Magnitude(m_rigidbody.velocity);
	m_rigidbody.velocity = direction * magnitude;
}

void Ball::Respawn()
{
	//TODO: settings file/class
	sf::Vector2f direction = sf::Vector2f(Random::Range(-0.5f, 0.5f), Random::Range(-1.0f, 0.1f));
	direction = VectorHelper::Normalize(direction);

	m_rigidbody.velocity = direction * 500.0f;

	m_collider.rectangle.left = 400.0f - m_sprite.getOrigin().x;
	m_collider.rectangle.top = 400.0f - m_sprite.getOrigin().y;
}

void Ball::HandleOnCollision(const HitInfo& hitInfo)
{
	bool isPaddle = dynamic_cast<Paddle*>(hitInfo.colliderB->actor) != nullptr;
	if (isPaddle == true)
	{
		//TODO: settings file/class
		// speed up the ball to a max
		float magnitude = VectorHelper::Magnitude(m_rigidbody.velocity);
		sf::Vector2f normal = m_rigidbody.velocity / magnitude;
		magnitude = Math::Min<float>(magnitude + 100.0f, 1500.0f);
		m_rigidbody.velocity = normal * magnitude;
	}
}

