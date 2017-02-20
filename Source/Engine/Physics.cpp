#include "Physics.h"

#include "Game/Actor.h"

Physics::Physics()
{
	m_dynamic.reserve(32);
	m_static.reserve(32);
}

Physics::~Physics()
{
}

void Physics::Update()
{
	//TODO: spatial partitioning

	// collision handling
	for (size_t i = 0; i < m_dynamic.size(); ++i)
	{
		if (m_dynamic[i] == nullptr)
			continue;

		Actor& a = *m_dynamic[i];

		// loop through dynamic
		for (size_t j = i+1; j < m_dynamic.size(); ++j)
		{
			if (m_dynamic[j] == nullptr)
				continue;

			Actor& b = *m_dynamic[j];
			CheckCollision(a, b);
		}

		// loop through static
		for (size_t j = 0; j < m_static.size(); ++j)
		{
			if (m_static[j] == nullptr)
				continue;

			Actor& b = *m_static[j];
			CheckCollision(a, b);
		}
	}
}

void Physics::CheckCollision(Actor& a, Actor& b)
{
	if (Actor::IsIntersecting(a, b) == true)
	{
		sf::Vector2f point;
		sf::Vector2f normal;

		HitInfo aInfo(point, normal, b);
		a.HandleOnCollision(aInfo);

		HitInfo bInfo(point, normal, a);
		b.HandleOnCollision(bInfo);
	}
}

void Physics::RegisterDynamic(Actor* actor)
{
	m_dynamic.push_back(actor);
}

void Physics::UnregisterDynamic(const Actor* actor)
{
	for (size_t i = 0; i < m_dynamic.size(); ++i)
	{
		if (m_dynamic[i] == actor)
		{
			m_dynamic.erase(m_dynamic.begin() + i);
			return;
		}
	}
}

void Physics::RegisterStatic(Actor* actor)
{
	m_static.push_back(actor);
}

void Physics::UnregisterStatic(const Actor* actor)
{
	for (size_t i = 0; i < m_static.size(); ++i)
	{
		if (m_static[i] == actor)
		{
			m_static.erase(m_static.begin() + i);
			return;
		}
	}
}
