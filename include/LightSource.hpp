#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "CollidableShape.hpp"
#include "Line.hpp"

class LightSource : public sf::Drawable, public sf::Transformable
{
public:
	LightSource();

	void update(std::vector<CollidableShape> &shapes);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setColor(const sf::Color& color);
	sf::Color getColor() const;

	void setDebugLinesEnabled(const bool& value);
	bool getDebugLinesEnabled() const;

	void setDebugLineColor(const sf::Color& color);
	sf::Color getDebugLineColor() const;

private:
	sf::Color _color;
	sf::Color _debugLineColor;
	bool _debugLinesEnabled;
	std::vector<sf::Vertex> _vertices;
	std::vector<sf::Vertex> calculatePolygonVertices(std::vector<Line> &lines);
};