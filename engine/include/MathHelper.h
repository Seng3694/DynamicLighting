#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Line.h"
#include "Nullable.h"

namespace seng
{
	class MathHelper
	{
	public:
		static int clamp(const int &value, const int &min, const int &max);
		static int circle(const int &value, const int &min, const int &max);

		static float length(const sf::Vector2f &vec);
		static float dot(const sf::Vector2f &left, const sf::Vector2f &right);
		static float cross(const sf::Vector2f &left, const sf::Vector2f &right);

		static bool isZero(const float &value);

		static float magnitude(const Line& line);
		static float magnitude(const sf::Vector2f& a, const sf::Vector2f& b);

		static float angle(const Line& line);
		static float angle(const sf::Vector2f& a, const sf::Vector2f& b);

		static Nullable<sf::Vector2f> intersection(const sf::Vector2f &a, const sf::Vector2f &b, const sf::Vector2f &c, const sf::Vector2f &d);
		static sf::Vector2f raycast(const sf::Vector2f &a, const sf::Vector2f &b, const std::vector<Line> &lines);
	};
}
