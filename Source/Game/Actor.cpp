#include "Actor.h"

bool Actor::IsIntersecting(const Actor& a, const Actor& b)
{
	return a.m_collider.intersects(b.m_collider);
}

