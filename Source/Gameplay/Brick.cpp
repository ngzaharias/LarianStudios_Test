#include "Brick.h"

#include "Game/Game.h"
#include "Gameplay/Ball.h"
#include "Gameplay/Map.h"

#include <SFML/Graphics.hpp>

Brick::Brick(const BrickSettings& settings)
{
	m_position = settings.position;

	m_sprite.setFillColor(sf::Color::Green);
	m_sprite.setPosition(settings.position);
	m_sprite.setSize(settings.size);

	m_sprite.setOrigin(settings.size / 2.0f);

	Game::Instance().GetPhysics().RegisterCollider(m_collider);
	m_collider.rectangle.width = settings.size.x;
	m_collider.rectangle.height = settings.size.y;
	m_collider.rectangle.left = settings.position.x - m_sprite.getOrigin().x;
	m_collider.rectangle.top = settings.position.y - m_sprite.getOrigin().y;
	m_collider.actor = this;
}

Brick::~Brick()
{
	Game::Instance().GetPhysics().UnregisterCollider(m_collider);
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
		Game::Instance().GetMap().UpdateScore(1);
		Game::Instance().GetMap().DestroyActor(this);
	}
}
