#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <functional>
#include <vector> 

class Actor;
struct Collider;

struct HitInfo
{
	sf::Vector2f point;
	sf::Vector2f normal;
	Collider* collider;

	HitInfo(Collider* collider)
		: collider(collider)
	{ }
};

struct Collider
{
	sf::FloatRect rectangle;
	std::function<void(HitInfo&)> callback;

	static bool IsIntersecting(const Collider& a, const Collider& b)
	{
		return a.rectangle.intersects(b.rectangle);
	}
};

struct Rigidbody
{
	sf::Vector2f velocity;
	Collider& collider;

	Rigidbody(Collider& collider)
		: collider(collider)
	{ }
};

class Physics
{
public:
	Physics();
	~Physics();

public:
	void Update();

	void CheckCollision(Collider& a, Collider& b);

	Collider& CreateCollider();
	void DestroyCollider(Collider& collider);

	Rigidbody& CreateRigidbody(Collider& collider);
	void DestroyRigidbody(Rigidbody& collider);

private:
	std::vector<Collider*> m_colliders;
	std::vector<Rigidbody*> m_rigidbodies;

};
#endif
