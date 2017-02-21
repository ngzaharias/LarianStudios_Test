#include "Paddle.h"

#include "Game/Game.h"
#include "Gameplay/Map.h"
#include "Engine/Physics.h"
#include "Engine/Screen.h"
#include "Utility/Math.h"

#include <SFML/Graphics.hpp>

Paddle::Paddle()
{
	m_position = sf::Vector2f(400.0f, 600.0f);

	m_sprite.setFillColor(sf::Color::White);
	m_sprite.setPosition(m_position);
	m_sprite.setSize(sf::Vector2f(250.0f, 30.0f));

	m_sprite.setOrigin(m_sprite.getSize() / 2.0f);

	m_collider = &Game::GetMap()->GetPhysics()->CreateCollider();
	m_collider->rectangle.width = m_sprite.getSize().x;
	m_collider->rectangle.height = m_sprite.getSize().y;
	m_collider->rectangle.left = m_position.x - m_sprite.getOrigin().x;
	m_collider->rectangle.top = m_position.y - m_sprite.getOrigin().y;
}

Paddle::~Paddle()
{
	Game::GetMap()->GetPhysics()->DestroyCollider(*m_collider);
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

	sf::RenderWindow* window = Screen::GetWindow();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	sf::Vector2f position = sf::Vector2f(mousePosition);
	
	float halfWidth = m_sprite.getSize().x / 2;
	m_position.x = Math::Clamp(position.x, 0.0f + halfWidth, Screen::width - halfWidth);

	// sync collider
	m_collider->rectangle.left = m_position.x - m_sprite.getOrigin().x;
	m_collider->rectangle.top = m_position.y - m_sprite.getOrigin().y;
}

void Paddle::Draw(sf::RenderWindow* window)
{
	Base::Draw(window);

	// sync sprite
	m_sprite.setPosition(m_position);
	window->draw(m_sprite);
}

