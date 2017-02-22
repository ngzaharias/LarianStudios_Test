#include "Brick.h"

#include "Game/Game.h"
#include "Gameplay/Ball.h"
#include "Gameplay/Map.h"

#include <SFML/Graphics.hpp>

Brick::Brick(sf::Vector2f position, sf::Vector2f size)
{
	m_position = position;

	m_sprite.setFillColor(sf::Color::Green);
	m_sprite.setPosition(m_position);
	m_sprite.setSize(size);

	m_sprite.setOrigin(m_sprite.getSize() / 2.0f);

	Game::GetPhysics()->RegisterCollider(m_collider);
	m_collider.rectangle.width = m_sprite.getSize().x;
	m_collider.rectangle.height = m_sprite.getSize().y;
	m_collider.rectangle.left = m_position.x - m_sprite.getOrigin().x;
	m_collider.rectangle.top = m_position.y - m_sprite.getOrigin().y;
	m_collider.actor = this;
}

Brick::~Brick()
{
	Game::GetPhysics()->UnregisterCollider(m_collider);
}

void Brick::Initialise()
{
	Base::Initialise();
	m_collider.callback = std::bind(&Brick::HandleOnCollision, this, std::placeholders::_1);
}

void Brick::Destroy()
{
	Base::Destroy();
}

void Brick::Update(float delta)
{
	Base::Update(delta);
}

void Brick::Draw(sf::RenderWindow* window)
{
	Base::Draw(window);

	m_sprite.setPosition(GetPosition());
	window->draw(m_sprite);
}

void Brick::HandleOnCollision(const HitInfo& hitInfo)
{
	bool isBall = dynamic_cast<Ball*>(hitInfo.colliderB->actor) != nullptr;
	if (isBall == true)
	{
		//TODO: settings
		Game::GetMap()->UpdateScore(1);
		Game::GetMap()->DestroyActor(this);
	}
}
