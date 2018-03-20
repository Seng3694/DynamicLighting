#pragma once

#include <SFML/Graphics.hpp>

struct Line : sf::Drawable
{
public:
	sf::Vertex a;
	sf::Vertex b;

	Line();
	Line(const sf::Vertex &av, const sf::Vertex &bv);
	Line(const sf::Vector2f &av, const sf::Vector2f &bv, const sf::Color &color);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};