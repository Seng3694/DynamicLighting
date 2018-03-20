#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Line.h"

int clamp(const int &value, const int &min, const int &max);
int circle(const int &value, const int &min, const int &max);

float length(const sf::Vector2f &vec);
float cross(const sf::Vector2f &left, const sf::Vector2f &right);
bool isZero(const float &value);

float magnitude(const Line& line);
float magnitude(const sf::Vector2f& a, const sf::Vector2f& b);

float angle(const Line& line);
float angle(const sf::Vector2f& a, const sf::Vector2f& b);

sf::Vector2f intersection(const Line& left, const Line& right);
sf::Vector2f raycast(const Line& line, const std::vector<Line>& lines);
sf::Vector2f raycast(const sf::Vector2f& start, const sf::Vector2f& end, const std::vector<Line>& lines);