#include "Ball.h"

#include "Game/Game.h"
#include "Gameplay/Map.h"
#include "Gameplay/Paddle.h"
#include "Engine/Physics.h"
#include "Utility/Math.h"
#include "Utility/Random.h"
#include "Utility/VectorHelper.h"

#include <SFML/Graphics.hpp>

Ball::Ball()
{
	//TODO: settings
	m_sprite.setFillColor(sf::Color::Green);
	m_sprite.setPosition(sf::Vector2f(400.0f, 400.0f));
	m_sprite.setSize(sf::Vector2f(20.0f, 20.0f));

	m_sprite.setOrigin(m_sprite.getSize() / 2.0f);

	m_collider = &Game::GetPhysics()->CreateCollider();
	m_collider->rectangle.width = m_sprite.getSize().x;
	m_collider->rectangle.height = m_sprite.getSize().y;
	m_collider->rectangle.left = m_sprite.getPosition().x - m_sprite.getOrigin().x;
	m_collider->rectangle.top = m_sprite.getPosition().y - m_sprite.getOrigin().y;
	m_collider->actor = this;

	m_rigidbody = &Game::GetPhysics()->CreateRigidbody(*m_collider);
}

Ball::~Ball()
{
	Game::GetPhysics()->DestroyCollider(*m_collider);
	Game::GetPhysics()->DestroyRigidbody(*m_rigidbody);
}

void Ball::Initialise()
{
	Base::Initialise();

	m_collider->callback = std::bind(&Ball::HandleOnCollision, this, std::placeholders::_1);

	float x = Random::Range(-500.0f, 500.0f);
	float y = Random::Range(-500.0f, 500.0f);
	m_rigidbody->velocity = sf::Vector2f(x, y);
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
	float x = m_rigidbody->collider.rectangle.left + m_sprite.getSize().x / 2;
	float y = m_rigidbody->collider.rectangle.top + m_sprite.getSize().y / 2;
	return sf::Vector2f(x, y);
}

void Ball::HandleOnCollision(const HitInfo& hitInfo)
{
	Paddle* paddle = dynamic_cast<Paddle*>(hitInfo.collider->actor);
	if (paddle != nullptr)
	{
		float magnitude = VectorHelper::Magnitude(m_rigidbody->velocity);
		sf::Vector2f normal = m_rigidbody->velocity / magnitude;
		magnitude = Math::Min(magnitude + 500.0f, 5000.0f);
		m_rigidbody->velocity = normal * magnitude;
		printf("Collision!");
	}
}

