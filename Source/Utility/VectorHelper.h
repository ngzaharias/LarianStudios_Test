#ifndef VECTOR_HELPER_H
#define VECTOR_HELPER_H

#include <SFML/System/Vector2.hpp>

#include <cmath>

namespace VectorHelper
{
	float Magnitude(const sf::Vector2f value)
	{
		float cSquared = value.x * value.x + value.y * value.y;
		return std::sqrt(cSquared);
	}

	sf::Vector2f Normalize(const sf::Vector2f value)
	{
		float magnitude = Magnitude(value);
		return value / magnitude;
	}
}

#endif
