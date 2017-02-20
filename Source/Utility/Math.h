#ifndef MATH_H
#define MATH_H

namespace Math
{
	float Clamp(float value, float min, float max)
	{
		return value < min ? min : value > max ? max : value;
	}
}

#endif