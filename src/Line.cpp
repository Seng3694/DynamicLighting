#include "Line.hpp"
#include <math.h>

Line::Line()
{
}

Line::Line(const sf::Vertex &av, const sf::Vertex &bv)
	: a(av), b(bv)
{
}

Line::Line(const sf::Vector2f &av, const sf::Vector2f &bv, const sf::Color &color)
	: a(sf::Vertex(av, color)), b(sf::Vertex(bv, color))
{
}

void Line::draw(sf::RenderTarget& target, const sf::RenderStates& states)
{
	sf::Vertex* vertices = new sf::Vertex[2]{ a, b };
	target.draw(vertices, 2, sf::PrimitiveType::Lines, states);
	delete[] vertices;
}