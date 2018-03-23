#include <stdlib.h>
#include <time.h>

#include "Random.h"

seng::Random::Random()
{
	setSeed(time(0));
}

unsigned int seng::Random::getSeed() const
{
	return _seed;
}

void seng::Random::setSeed(const unsigned int &seed)
{
	_seed = seed;
	srand(seed);
}

int seng::Random::next() const
{
	return rand();
}

int seng::Random::range(const int &fromIncl, const int &toIncl) const
{
	auto range = toIncl - fromIncl + 1;
	return (rand() % range) + fromIncl;
}