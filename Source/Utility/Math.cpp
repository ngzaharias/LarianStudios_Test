#include "Math.h"

namespace Math
{
	float Clamp(float value, float min, float max)
	{
		return value < min ? min : value > max ? max : value;
	}

	float Min(float a, float b)
	{
		return (a < b) ? a : b;
	}

	float Max(float a, float b)
	{
		return (a > b) ? a : b;
	}

	float Sign(float value)
	{
		return (value < 0.0f) ? -1.0f : 1.0f;
	}
}