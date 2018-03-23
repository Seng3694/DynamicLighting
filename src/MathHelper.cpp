#include <math.h>
#include <limits>

#include "MathHelper.h"

#ifndef FLT_EPSILON
#define FLT_EPSILON 1.192092896e-07F // smallest such that 1.0+FLT_EPSILON != 1.0
#endif

int MathHelper::clamp(const int &value, const int &min, const int &max)
{
	if (value > max) return max;
	if (value < min) return min;
	return value;
}

int MathHelper::circle(const int &value, const int &min, const int &max)
{
	if (value > max) return min;
	if (value < min) return max;
	return value;
}

float MathHelper::length(const sf::Vector2f &vec)
{
	return sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
}

//normally the cross product is not possible in 2D
//this will return the Z component of the cross product in a 3D environment
float MathHelper::cross(const sf::Vector2f &left, const sf::Vector2f &right)
{
	return left.x * right.y - left.y * right.x;
}

float MathHelper::dot(const sf::Vector2f &left, const sf::Vector2f &right)
{
	return left.x * right.y + left.y * right.x;
}

bool MathHelper::isZero(const float &value)
{
	return fabs(value) < FLT_EPSILON;
}

float MathHelper::magnitude(const Line& line)
{
	return magnitude(line.a.position, line.b.position);
}

float MathHelper::magnitude(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
}

float MathHelper::angle(const Line& line)
{
	return angle(line.a.position, line.b.position);
}

float MathHelper::angle(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return atan2f(b.y - a.y, b.x - a.x);
}

//explanation: https://www.youtube.com/watch?v=c065KoXooSw
Nullable<sf::Vector2f> MathHelper::intersection(const sf::Vector2f &a1, const sf::Vector2f &b1, const sf::Vector2f &a2, const sf::Vector2f &b2)
{
	auto r = b1 - a1;
	auto s = b2 - a2;

	auto d = cross(r, s);

	//if the cross product of two 2D vectors is zero, the lines are parallel which means they are either infinite intersections or none
	if (isZero(d))
		return Nullable<sf::Vector2f>();

	auto u = ((a2.x - a1.x) * r.y - (a2.y - a1.y) * r.x) / d;
	auto t = ((a2.x - a1.x) * s.y - (a2.y - a1.y) * s.x) / d;

	//function for every vector on A1B1:  a1 + t * r
	//the value of "u" determines whether the intersection is on A2 (0), between A2 and B2 (>0 && <1) or on B2 (1)
	//if the value is less than 0 or bigger than 1, then the intersection is not on the line
	//same for the line A1B1 and the factor t
	//because we are casting from source (A1) to "infinity", we don't check if t is <= 1
	if (u >= 0 && u <= 1 && t >= 0) 
		return a1 + (t * r);

	return Nullable<sf::Vector2f>();
}

sf::Vector2f MathHelper::raycast(const sf::Vector2f &a, const sf::Vector2f &b, const std::vector<Line> &lines)
{
	float shortest = std::numeric_limits<float>::max();
	auto shortestIntersection = Nullable<sf::Vector2f>();
	float longest = magnitude(a, b);
	auto longestIntersection = b;

	//check intersection of every line and calculate the distance to the intersection point
	//the smallest intersection will be returned. if there is no smallest intersection, the highest will be returned
	for (auto l : lines)
	{
		auto i = intersection(a, b, l.a.position, l.b.position);

		if (i.hasValue())
		{
			auto mag = magnitude(a, i);

			if (mag < shortest)
			{
				shortest = mag;
				shortestIntersection = i;
			}
			if (mag > longest)
			{
				longest = mag;
				longestIntersection = i;
			}
		}
	}

	if (shortestIntersection.hasValue())
		return shortestIntersection;
	else
		return longestIntersection;
}