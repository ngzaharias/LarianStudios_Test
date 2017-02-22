#ifndef RANDOM_H
#define RANDOM_H


namespace Random
{
	//TODO: specify allowed types
	template<typename T> T Range(const T& min, const T& max)
	{
		T r = std::rand() / (T)RAND_MAX;
		return (r * (max - min)) + min;
	}
}

#endif