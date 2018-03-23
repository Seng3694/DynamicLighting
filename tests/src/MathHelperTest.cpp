#include <math.h>
#include <vector>

#include <SFML/Graphics.hpp>

#include "catch.h"

#include "Line.h"
#include "MathHelper.h"

TEST_CASE("engine/MathHelper clamp()")
{
	auto lower = 0;
	auto upper = 10;

	REQUIRE(seng::MathHelper::clamp(0, lower, upper) == 0);
	REQUIRE(seng::MathHelper::clamp(10, lower, upper) == 10);
	REQUIRE(seng::MathHelper::clamp(5, lower, upper) == 5);
	REQUIRE(seng::MathHelper::clamp(-1, lower, upper) == lower);
	REQUIRE(seng::MathHelper::clamp(11, lower, upper) == upper);
}

TEST_CASE("engine/MathHelper circleClamp()")
{
	auto lower = 0;
	auto upper = 10;

	REQUIRE(seng::MathHelper::circleClamp(0, lower, upper) == 0);
	REQUIRE(seng::MathHelper::circleClamp(10, lower, upper) == 10);
	REQUIRE(seng::MathHelper::circleClamp(5, lower, upper) == 5);
	REQUIRE(seng::MathHelper::circleClamp(-1, lower, upper) == upper);
	REQUIRE(seng::MathHelper::circleClamp(11, lower, upper) == lower);
}

TEST_CASE("engine/MathHelper length()")
{
	sf::Vector2f vec(3, 4);

	REQUIRE(seng::MathHelper::length(vec) == sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST_CASE("engine/MathHelper cross()")
{
	sf::Vector2f left(2, 3);
	sf::Vector2f right(4, 5);

	REQUIRE(seng::MathHelper::cross(left, right) == left.x * right.y - left.y * right.x);
}

TEST_CASE("engine/MathHelper dot()")
{
	sf::Vector2f left(2, 3);
	sf::Vector2f right(4, 5);

	REQUIRE(seng::MathHelper::dot(left, right) == left.x * right.y + left.y * right.x);
}

TEST_CASE("engine/MathHelper isZero()")
{
	float f1 = 0.0000001f;
	float f2 = 0.0000002f;

	REQUIRE(seng::MathHelper::isZero(f1) == true);
	REQUIRE(seng::MathHelper::isZero(f2) == false);
}

TEST_CASE("engine/MathHelper magnitude()")
{
	sf::Vector2f left(2, 3);
	sf::Vector2f right(4, 5);

	REQUIRE(seng::MathHelper::magnitude(left, right) == sqrtf(powf(left.x - right.x, 2) + powf(left.y - right.y, 2)));
}

TEST_CASE("engine/MathHelper angle()")
{
	sf::Vector2f left(2, 3);
	sf::Vector2f right(4, 5);

	REQUIRE(seng::MathHelper::angle(left, right) == atan2f(right.y - left.y, right.x - left.x));
}

TEST_CASE("engine/MathHelper check clear intersection()")
{
	sf::Vector2f a(0, 0);
	sf::Vector2f b(1, 1);
	sf::Vector2f c(1, 0);
	sf::Vector2f d(0, 1);

	sf::Vector2f expected(0.5f, 0.5f);
	auto intersection = seng::MathHelper::intersection(a, b, c, d);

	REQUIRE(intersection.hasValue());
	REQUIRE(intersection.getValue().x == expected.x);
	REQUIRE(intersection.getValue().y == expected.y);
}

TEST_CASE("engine/MathHelper check parallel intersection()")
{
	sf::Vector2f a(0, 0);
	sf::Vector2f b(1, 0);
	sf::Vector2f c(0, 1);
	sf::Vector2f d(1, 1);

	auto intersection = seng::MathHelper::intersection(a, b, c, d);

	REQUIRE(intersection.hasValue() == false);
}

TEST_CASE("engine/MathHelper check close pass intersection()")
{
	sf::Vector2f a(0, 0);
	sf::Vector2f b(3, 1.9f);
	sf::Vector2f c(3, 4);
	sf::Vector2f d(3, 2);

	auto intersection = seng::MathHelper::intersection(a, b, c, d);

	REQUIRE(intersection.hasValue() == false);
}

TEST_CASE("engine/MathHelper check on same line intersection()")
{
	sf::Vector2f a(0, 0);
	sf::Vector2f b(3, 0);
	sf::Vector2f c(1, 0);
	sf::Vector2f d(4, 0);

	auto intersection = seng::MathHelper::intersection(a, b, c, d);

	REQUIRE(intersection.hasValue() == false);
}

TEST_CASE("engine/MathHelper check ray cast intersection()")
{
	sf::Vector2f a(0, 0);
	sf::Vector2f b(1, 1);
	sf::Vector2f c(4, 30);
	sf::Vector2f d(4, 0);

	auto intersection = seng::MathHelper::intersection(a, b, c, d);

	REQUIRE(intersection.hasValue() == true);
}


TEST_CASE("engine/MathHelper check raycast() against three lines")
{
	sf::Vector2f a(0, 0);
	sf::Vector2f b(10, 0);
	std::vector<seng::Line> lines;

	lines.push_back(seng::Line(sf::Vector2f(3, -3), sf::Vector2f(3, 3), sf::Color::Black));
	lines.push_back(seng::Line(sf::Vector2f(6, -3), sf::Vector2f(6, 3), sf::Color::Black));
	lines.push_back(seng::Line(sf::Vector2f(9, -3), sf::Vector2f(9, 3), sf::Color::Black));

	auto firstIntersection = seng::MathHelper::raycast(a, b, lines);

	REQUIRE(firstIntersection.x == 3);
}

TEST_CASE("engine/MathHelper check raycast() against three lines which won't get hit")
{
	sf::Vector2f a(0, 0);
	sf::Vector2f b(10, 0);
	std::vector<seng::Line> lines;

	lines.push_back(seng::Line(sf::Vector2f(3, -3), sf::Vector2f(3, -2), sf::Color::Black));
	lines.push_back(seng::Line(sf::Vector2f(6, -3), sf::Vector2f(6, -2), sf::Color::Black));
	lines.push_back(seng::Line(sf::Vector2f(9, -3), sf::Vector2f(9, -2), sf::Color::Black));

	auto firstIntersection = seng::MathHelper::raycast(a, b, lines);

	REQUIRE(firstIntersection.x == b.x);
	REQUIRE(firstIntersection.y == b.y);
}