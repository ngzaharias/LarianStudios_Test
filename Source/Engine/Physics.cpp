#include "Physics.h"

#include "Game/Actor.h"
#include "Utility/Math.h"
#include "Utility/VectorHelper.h"

Physics::Physics()
{
	m_colliders.reserve(64);
	m_rigidbodies.reserve(32);
}

Physics::~Physics()
{
}

void Physics::Update(float delta)
{
	//TODO: spatial partitioning

	// collision handling
	std::vector<Rigidbody*>::iterator rigidbody = m_rigidbodies.begin();
	std::vector<Rigidbody*>::iterator rigidbodyEnd = m_rigidbodies.end();
	for (; rigidbody != rigidbodyEnd; ++rigidbody)
	{
		Rigidbody& a = *(*rigidbody);
		if (a.collider != nullptr)
		{

			// loop through static objects
			bool isColliding = false;
			std::vector<Collider*>::iterator collider = m_colliders.begin();
			std::vector<Collider*>::iterator colliderEnd = m_colliders.end();
			for (; collider != colliderEnd; ++collider)
			{
				if ((*collider) != a.collider)
				{
					Collider& b = *(*collider);
					if (CheckCollision(a, b, delta) == true)
					{
						HandleCollision(a, b, delta);
					}
				}
			}

			a.collider->rectangle.left += a.velocity.x * delta;
			a.collider->rectangle.top += a.velocity.y * delta;
		}
	}
}

bool Physics::CheckCollision(Rigidbody& rigidbody, Collider& collider, float delta)
{
	if (rigidbody.collider == nullptr)
		return false;

	//TODO: physics stepping
	Collider step = *rigidbody.collider;
	step.rectangle.left += rigidbody.velocity.x * delta;
	step.rectangle.top += rigidbody.velocity.y * delta;

	if (Collider::IsIntersecting(step, collider) == false)
		return false;

	return true;
}

void Physics::HandleCollision(Rigidbody& rigidbody, Collider& collider, float delta)
{
	Collider& b1 = *rigidbody.collider;
	Collider& b2 = collider;
	Collider step = b1;
	step.rectangle.left += rigidbody.velocity.x * delta;
	step.rectangle.top += rigidbody.velocity.y * delta;

	// distance of box 'b2' to face on 'left' side of 'b1'.
	// distance of box 'b2' to face on 'right' side of 'b1'
	// distance of box 'b2' to face on 'top' side of 'b1'.
	// distance of box 'b2' to face on 'bottom' side of 'b1'.
	float left = (b2.rectangle.left + b2.rectangle.width) - step.rectangle.left;
	float right = (step.rectangle.left + step.rectangle.width) - b2.rectangle.left;
	float top = (step.rectangle.top + step.rectangle.height) - b2.rectangle.top;
	float bottom = (b2.rectangle.top + b2.rectangle.height) - step.rectangle.top;

	//TODO: move rigidbody out of the collider

	//HACK: not exactly the best way to get a hit normal
	sf::Vector2f normal;
	float minX = Math::Min<float>(left, right);
	float minY = Math::Min<float>(top, bottom);
	normal.x = (minX < minY) ? (left < right) ? -1.0f : 1.0f : 0.0f;
	normal.y = (minX < minY) ? 0.0f : (top < bottom) ? -1.0f : 1.0f;

	if (b2.isTrigger == false)
	{
		rigidbody.velocity = VectorHelper::Reflect(rigidbody.velocity, normal);
	}

	HitInfo box1Info;
	box1Info.colliderA = &b1;
	box1Info.colliderB = &b2;
	box1Info.normal = normal;
	if (b1.callback != nullptr)
	{
		b1.callback(box1Info);
	}

	HitInfo box2Info;
	box2Info.colliderA = &b2;
	box2Info.colliderB = &b1;
	box2Info.normal = normal * -1.0f;
	if (b2.callback != nullptr)
	{
		b2.callback(box2Info);
	}
}


void Physics::RegisterCollider(Collider& collider)
{
	m_colliders.push_back(&collider);
}

void Physics::UnregisterCollider(Collider& collider)
{
	std::vector<Collider*>::iterator itr = m_colliders.begin();
	std::vector<Collider*>::iterator end = m_colliders.end();
	for (; itr != end; ++itr)
	{
		Collider& value = *(*itr);
		if (&value == &collider)
		{
			m_colliders.erase(itr);
			return;
		}
	}
}

void Physics::RegisterRigidbody(Rigidbody& rigidbody)
{
	m_rigidbodies.push_back(&rigidbody);
}

void Physics::UnregisterRigidbody(Rigidbody& rigidbody)
{
	std::vector<Rigidbody*>::iterator itr = m_rigidbodies.begin();
	std::vector<Rigidbody*>::iterator end = m_rigidbodies.end();
	for (; itr != end; ++itr)
	{
		Rigidbody& value = *(*itr);
		if (&value == &rigidbody)
		{
			m_rigidbodies.erase(itr);
			return;
		}
	}
}
