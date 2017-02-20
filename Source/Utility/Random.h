#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace Random
{
	float Range(float min, float max)
	{
		float r = std::rand() / (float)RAND_MAX;
		return ( r * (max - min)) + min;
	}
}

#endif