#include "VectorHelper.h"

#include <cmath>

namespace VectorHelper
{
	float Dot(const sf::Vector2f& a, const sf::Vector2f& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	float Magnitude(const sf::Vector2f& value)
	{
		float cSquared = value.x * value.x + value.y * value.y;
		return std::sqrt(cSquared);
	}

	sf::Vector2f Normalize(const sf::Vector2f& value)
	{
		//TODO: handle (0,0) vector?
		float magnitude = Magnitude(value);
		return value / magnitude;
	}

	sf::Vector2f Reflect(const sf::Vector2f& vector, const sf::Vector2f& normal)
	{
		// Vnew = -2 * (V dot N)*N + V
		float dot2 = Dot(vector, normal) * -2.0f;
		return (dot2 * normal) + vector;
	}
}
