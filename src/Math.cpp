#include "Math.hpp"

#include <math.h>
#include <limits>

float magnitude(const Line& line)
{
	return magnitude(line.a.position, line.b.position);
}

float magnitude(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return sqrtf(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

float angle(const Line& line)
{
	return angle(line.a.position, line.b.position);
}

float angle(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return atan2f(b.y - a.y, b.x - a.x);
}

sf::Vector2f intersection(const Line& left, const Line& right)
{
	float l_px = left.a.position.x;
	float l_py = left.a.position.y;
	float l_dx = left.b.position.x - left.a.position.x;
	float l_dy = left.b.position.y - left.a.position.y;

	float r_px = right.a.position.x;
	float r_py = right.a.position.y;
	float r_dx = right.b.position.x - right.a.position.x;
	float r_dy = right.b.position.y - right.a.position.y;

	float l_mag = magnitude(left);
	float r_mag = magnitude(right);

	if (l_dx / l_mag == r_dx / r_mag &&
		l_dy / l_mag == r_dy / r_mag)
		return sf::Vector2f(-1, -1);

	float T2 = (l_dx * (r_py - l_py) + l_dy * (l_px - r_px)) / (r_dx * l_dy - r_dy * l_dx);
	float T1 = (r_px + r_dx * T2 - l_px) / l_dx;

	if (T1 < 0) return sf::Vector2f(-1, -1);
	if (T2 < 0 || T2 > 1) return sf::Vector2f(-1, -1);

	return sf::Vector2f(l_px + l_dx * T1, l_py + l_dy * T1);
}


sf::Vector2f raycast(const sf::Vector2f& start, const sf::Vector2f& end, const std::vector<Line>& lines)
{
	return raycast(Line{ start, end, sf::Color::Transparent }, lines);
}

sf::Vector2f raycast(const Line& line, const std::vector<Line>& lines)
{
	float shortest = std::numeric_limits<float>::max();
	auto shortestIntersection = sf::Vector2f{ -1, -1 };
	auto lineMag = magnitude(line);

	for (auto l : lines)
	{
		auto i = intersection(line, l);

		if (i.x != -1 && i.y != -1)
		{
			auto mag = magnitude(line.a.position, i);

			if (mag < shortest)
			{
				shortest = mag;
				shortestIntersection = i;
			}
		}
	}

	return shortestIntersection;
}