#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <functional>
#include <vector> 

class Actor;
struct Collider;

// ColliderA will always be the owner of the callback
struct HitInfo
{
	sf::Vector2f normal;
	Collider* colliderA = nullptr;
	Collider* colliderB = nullptr;
};

struct Collider
{
	sf::FloatRect rectangle;
	std::function<void(HitInfo&)> callback = nullptr;
	Actor* actor = nullptr;
	bool isTrigger = false;

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

	bool CheckCollision(const Rigidbody& a, const Collider& b, float delta) const;
	void HandleCollision(Rigidbody& a, Collider& b, float delta);

	void RegisterCollider(Collider& collider);
	void UnregisterCollider(const Collider& collider);

	void RegisterRigidbody(Rigidbody& rigidbody);
	void UnregisterRigidbody(const Rigidbody& rigidbody);

private:
	std::vector<Collider*> m_colliders;
	std::vector<Rigidbody*> m_rigidbodies;

};
#endif
