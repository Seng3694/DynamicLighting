#include <stdlib.h>
#include <time.h>

#include "Random.hpp"

Random::Random()
{
	setSeed(time(0));
}

unsigned int Random::getSeed() const
{
	return _seed;
}

void Random::setSeed(const unsigned int &seed)
{
	_seed = seed;
	srand(seed);
}

int Random::next() const
{
	return rand();
}

int Random::range(const int &fromIncl, const int &toIncl) const
{
	auto range = toIncl - fromIncl + 1;
	return (rand() % range) + fromIncl;
}