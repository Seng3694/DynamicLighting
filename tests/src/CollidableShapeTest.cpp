#include <SFML/Graphics.hpp>

#include "catch.h"

#include "CollidableShape.h"

TEST_CASE("engine/CollidableShape check getLines() without reloading")
{
	auto shape = sf::CircleShape();
	shape.setPointCount(10);
	auto collidableShape = seng::CollidableShape(&shape);
	
	auto lines = collidableShape.getLines();
	REQUIRE(lines.size() == 0);
}

TEST_CASE("engine/CollidableShape check reloadLines() and getLines()")
{
	auto shape = sf::CircleShape();
	shape.setPointCount(10);
	auto collidableShape = seng::CollidableShape(&shape);

	collidableShape.reloadLines();
	auto lines = collidableShape.getLines();
	REQUIRE(lines.size() == shape.getPointCount());
}


TEST_CASE("engine/CollidableShape check reloadLines() after setting point count new")
{
	auto shape = sf::CircleShape();
	shape.setPointCount(10);
	auto collidableShape = seng::CollidableShape(&shape);

	collidableShape.reloadLines();
	shape.setPointCount(12);
	collidableShape.reloadLines();

	auto lines = collidableShape.getLines();
	REQUIRE(lines.size() == shape.getPointCount());
}