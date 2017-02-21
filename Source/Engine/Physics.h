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
	sf::Vector2f normal;
	Collider* collider = nullptr;
};

struct Collider
{
	sf::FloatRect rectangle;
	std::function<void(HitInfo&)> callback = nullptr;
	Actor* actor = nullptr;

	static bool IsIntersecting(const Collider& a, const Collider& b)
	{
		return a.rectangle.intersects(b.rectangle);
	}
};

struct Rigidbody
{
	sf::Vector2f velocity;
	Collider* collider = nullptr;
};

class Physics
{
public:
	Physics();
	~Physics();

public:
	void Update(float delta);

	bool CheckCollision(Rigidbody& a, Collider& b, float delta);
	void HandleCollision(Rigidbody& a, Collider& b, float delta);

	void RegisterCollider(Collider& collider);
	void UnregisterCollider(Collider& collider);

	void RegisterRigidbody(Rigidbody& rigidbody);
	void UnregisterRigidbody(Rigidbody& rigidbody);

private:
	std::vector<Collider*> m_colliders;
	std::vector<Rigidbody*> m_rigidbodies;

};
#endif
