#include "Paddle.h"

#include "Game/Game.h"
#include "Gameplay/Ball.h"
#include "Gameplay/Map.h"
#include "Engine/Physics.h"
#include "Engine/Screen.h"

#include "Utility/Math.h"
#include "Utility/VectorHelper.h"

#include <SFML/Graphics.hpp>

Paddle::Paddle()
{
	m_position = sf::Vector2f(400.0f, 535.0f);

	m_sprite.setFillColor(sf::Color::White);
	m_sprite.setPosition(m_position);
	m_sprite.setSize(sf::Vector2f(250, 30));

	m_sprite.setOrigin(m_sprite.getSize() / 2.0f);

	// colliders
	InitaliseColliders();
}

Paddle::~Paddle()
{
	Game::GetPhysics()->UnregisterCollider(m_colliderLeft);
	Game::GetPhysics()->UnregisterCollider(m_colliderRight);
}

void Paddle::Initialise()
{
	Base::Initialise();
}

void Paddle::Destroy()
{
	Base::Destroy();
}

void Paddle::Update(float delta)
{
	Base::Update(delta);

	//TODO: limit paddle speed?

	sf::Window* window = Screen::GetWindow();
	sf::Vector2i screenPosition = sf::Mouse::getPosition(*window);
	sf::Vector2i position = Screen::AdjustToFullscreenPosition(*window, screenPosition);
	
	m_position.x = (float)Math::Clamp<int>(position.x, 0, (int)Screen::width);

	// sync collider
	SyncColliders();
}

void Paddle::Draw(sf::RenderWindow* window)
{
	Base::Draw(window);

	// sync sprite
	m_sprite.setPosition(GetPosition());
	window->draw(m_sprite);

	Debug_DrawColliders(window);
}

void Paddle::HandleOnCollision(const HitInfo& hitInfo)
{
	Ball* ball = dynamic_cast<Ball*>(hitInfo.colliderB->actor);
	if (ball != nullptr)
	{
		bool isLeft = hitInfo.colliderA == &m_colliderLeft;

		sf::Vector2f direction = sf::Vector2f(0.0f, -1.0f);
		direction.x += (isLeft) ? -1.0f : 1.0f;
		direction = VectorHelper::Normalize(direction);

		ball->SetDirection(direction);
	}
}

void Paddle::InitaliseColliders()
{
	Game::GetPhysics()->RegisterCollider(m_colliderLeft);
	Game::GetPhysics()->RegisterCollider(m_colliderRight);

	float colliderWidth = m_sprite.getSize().x / 2;
	m_colliderLeft.rectangle.width = colliderWidth;
	m_colliderLeft.rectangle.height = m_sprite.getSize().y;
	m_colliderLeft.actor = this;
	m_colliderLeft.callback = std::bind(&Paddle::HandleOnCollision, this, std::placeholders::_1);

	m_colliderRight.rectangle.width = colliderWidth;
	m_colliderRight.rectangle.height = m_sprite.getSize().y;
	m_colliderRight.actor = this;
	m_colliderRight.callback = std::bind(&Paddle::HandleOnCollision, this, std::placeholders::_1);

	SyncColliders();
}

void Paddle::SyncColliders()
{
	float colliderWidth = m_sprite.getSize().x / 2;
	m_colliderLeft.rectangle.left = m_position.x - m_sprite.getOrigin().x + (colliderWidth * 0);
	m_colliderLeft.rectangle.top = m_position.y - m_sprite.getOrigin().y;

	m_colliderRight.rectangle.left = m_position.x - m_sprite.getOrigin().x + (colliderWidth * 1);
	m_colliderRight.rectangle.top = m_position.y - m_sprite.getOrigin().y;
}

void Paddle::Debug_DrawColliders(sf::RenderWindow* window)
{
	float colliderWidth = m_sprite.getSize().x / 2;
	sf::RectangleShape left = sf::RectangleShape();
	sf::RectangleShape right = sf::RectangleShape();

	left.setSize(sf::Vector2f(colliderWidth, m_sprite.getSize().y));
	right.setSize(sf::Vector2f(colliderWidth, m_sprite.getSize().y));

	left.setPosition(sf::Vector2f(m_colliderLeft.rectangle.left, m_colliderLeft.rectangle.top));
	right.setPosition(sf::Vector2f(m_colliderRight.rectangle.left, m_colliderRight.rectangle.top));

	left.setFillColor(sf::Color::Blue);
	right.setFillColor(sf::Color::Blue);

	window->draw(left);
	window->draw(right);
}