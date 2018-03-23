#include <set>

#include "catch.h"

#include "Random.h"

TEST_CASE("engine/Random check next() without explicit seed")
{
	seng::Random rnd;
	
	std::set<int> results;

	for (unsigned int i = 0; i < 10000; i++)
	{
		int value = rnd.next();
		results.emplace(value);
	}

	REQUIRE(results.empty() == false);
}

TEST_CASE("engine/Random check range() without explicit seed")
{
	seng::Random rnd;
	std::set<int> results;
	int start = -5;
	int end = 5;

	for (unsigned int i = 0; i < 10000; i++)
	{
		int value = rnd.range(start, end);
		REQUIRE(value >= start);
		REQUIRE(value <= end);
		results.emplace(value);
	}

	REQUIRE(results.size() == end - start + 1);
}