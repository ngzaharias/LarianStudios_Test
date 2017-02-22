#include "Paddle.h"

#include "Game/Game.h"
#include "Gameplay/Ball.h"
#include "Gameplay/Map.h"
#include "Engine/Physics.h"
#include "Engine/Screen.h"
#include "Utility/Math.h"
#include "Utility/VectorHelper.h"

#include <SFML/Graphics.hpp>

Paddle::Paddle(const PaddleSettings& settings)
{
	m_position = settings.position;

	m_sprite.setFillColor(sf::Color::White);
	m_sprite.setOrigin(settings.size / 2.0f);
	m_sprite.setPosition(m_position);
	m_sprite.setSize(settings.size);

	Game::Instance().GetPhysics().RegisterCollider(m_collider);
	m_collider.rectangle.width = settings.size.x;
	m_collider.rectangle.height = settings.size.y;
	m_collider.actor = this;

	m_collider.callback = std::bind(&Paddle::HandleOnCollision, this, std::placeholders::_1);

	SyncColliders();
}

Paddle::~Paddle()
{
	Game::Instance().GetPhysics().UnregisterCollider(m_collider);
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
	
	float target = (float)Math::Clamp<int>(position.x, 0, (int)Screen::width);
	m_position.x += (target - m_position.x) * 100.0f * delta;

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
		sf::Vector2f ballPosition = ball->GetPosition();
		sf::Vector2f paddlePosition = this->GetPosition();
		sf::Vector2f normal = VectorHelper::Normalize(ballPosition - paddlePosition);

		float dot = VectorHelper::Dot(normal, sf::Vector2f(0.0f, -1.0f)); 
		float influenceX = Math::Clamp(normal.x, -1.0f, 1.0f);
		float influenceY = -Math::Clamp(dot + 0.2f, 0.0f, 1.0f);
		sf::Vector2f direction = sf::Vector2f(influenceX, influenceY);
		ball->InfluenceDirection(direction);
	}
}


void Paddle::SyncColliders()
{
	m_collider.rectangle.left = m_position.x - m_sprite.getOrigin().x;
	m_collider.rectangle.top = m_position.y - m_sprite.getOrigin().y;
}

void Paddle::Debug_DrawColliders(sf::RenderWindow* window)
{
	sf::RectangleShape box = sf::RectangleShape();
	box.setPosition(sf::Vector2f(m_collider.rectangle.left, m_collider.rectangle.top));
	box.setSize(sf::Vector2f(m_sprite.getSize().x, m_sprite.getSize().y));
	box.setFillColor(sf::Color::Blue);
	window->draw(box);
}