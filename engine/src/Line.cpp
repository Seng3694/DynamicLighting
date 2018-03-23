#include <math.h>

#include "Line.h"

seng::Line::Line()
{
}

seng::Line::Line(const sf::Vertex &av, const sf::Vertex &bv)
	: a(av), b(bv)
{
}

seng::Line::Line(const sf::Vector2f &av, const sf::Vector2f &bv, const sf::Color &color)
	: a(sf::Vertex(av, color)), b(sf::Vertex(bv, color))
{
}

void seng::Line::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(&a, 2, sf::PrimitiveType::Lines, states);
}