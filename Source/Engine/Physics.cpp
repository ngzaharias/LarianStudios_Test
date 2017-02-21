#include "Physics.h"

#include "Game/Actor.h"

Physics::Physics()
{
	m_colliders.reserve(64);
	m_rigidbodies.reserve(32);
}

Physics::~Physics()
{
}

void Physics::Update()
{
	//TODO: spatial partitioning

	// collision handling
	std::vector<Rigidbody*>::iterator rigidbody = m_rigidbodies.begin();
	std::vector<Rigidbody*>::iterator rigidbodyEnd = m_rigidbodies.end();
	for (; rigidbody != rigidbodyEnd; ++rigidbody)
	{
		if ((*rigidbody) != nullptr)
		{
			Rigidbody& a = *(*rigidbody);

			// loop through static objects
			std::vector<Collider*>::iterator collider = m_colliders.begin();
			std::vector<Collider*>::iterator colliderEnd = m_colliders.end();
			for (; collider != colliderEnd; ++collider)
			{
				if ((*collider) != nullptr && (*collider) != &a.collider)
				{
					Collider& b = *(*collider);
					CheckCollision(a.collider, b);
				}
			}
		}
	}
}

void Physics::CheckCollision(Collider& a, Collider& b)
{
	if (Collider::IsIntersecting(a, b) == true)
	{
		sf::Vector2f point;
		sf::Vector2f normal;

		HitInfo aInfo(&b);
		aInfo.normal = normal;
		aInfo.point = point;
		if (a.callback != nullptr)
		{
			a.callback(aInfo);
		}

		HitInfo bInfo(&a);
		bInfo.normal = normal * -1.0f;
		bInfo.point = point;
		if (b.callback != nullptr)
		{
			b.callback(bInfo);
		}
	}
}

Collider& Physics::CreateCollider()
{
	Collider* collider = new Collider();
	m_colliders.push_back(collider);
	return *collider;
}

void Physics::DestroyCollider(Collider& collider)
{
	std::vector<Collider*>::iterator itr = m_colliders.begin();
	std::vector<Collider*>::iterator end = m_colliders.end();
	for (; itr != end; ++itr)
	{
		Collider* value = *itr;
		if (value != nullptr && value == &collider)
		{
			m_colliders.erase(itr);
			delete value;
			return;
		}
	}
}

Rigidbody& Physics::CreateRigidbody(Collider& collider)
{
	Rigidbody* rigidbody = new Rigidbody(collider);
	m_rigidbodies.push_back(rigidbody);
	return *rigidbody;
}

void Physics::DestroyRigidbody(Rigidbody& rigidbody)
{
	std::vector<Rigidbody*>::iterator itr = m_rigidbodies.begin();
	std::vector<Rigidbody*>::iterator end = m_rigidbodies.end();
	for (; itr != end; ++itr)
	{
		Rigidbody* value = *itr;
		if (value != nullptr && value == &rigidbody)
		{
			m_rigidbodies.erase(itr);
			delete value;
			return;
		}
	}
}
