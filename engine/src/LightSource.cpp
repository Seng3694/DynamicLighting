#include <algorithm>
#include <set>

#include "LightSource.h"
#include "MathHelper.h"

seng::LightSource::LightSource()
	: _debugLineColor(sf::Color::Red), _color(sf::Color::Yellow), _isStatic(false), _staticAfterUpdate(false)
{
}

void seng::LightSource::setColor(const sf::Color& color)
{
	_color = color;
}

sf::Color seng::LightSource::getColor() const
{
	return _color;
}

void seng::LightSource::setDebugLineColor(const sf::Color& color)
{
	_debugLineColor = color;
}

sf::Color seng::LightSource::getDebugLineColor() const
{
	return _debugLineColor;
}

void seng::LightSource::setDebugLinesEnabled(const bool& value)
{
	_debugLinesEnabled = value;
}

bool seng::LightSource::getDebugLinesEnabled() const
{
	return _debugLinesEnabled;
}

void seng::LightSource::setIsStatic(const bool& value)
{
	if (value == true && !_isStatic)
	{
		_staticAfterUpdate = true;
	}
	else if (value == false)
	{
		_isStatic = false;
		_staticAfterUpdate = false;
	}
}

bool seng::LightSource::getIsStatic() const
{
	return _isStatic;
}

void seng::LightSource::update(std::vector<seng::Line> &lines)
{
	if (_isStatic == false)
	{
		_vertices = calculatePolygonVertices(lines);

		if (_staticAfterUpdate)
		{
			_isStatic = true;
			_staticAfterUpdate = false;
		}
	}
}

void seng::LightSource::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(&_vertices[0], _vertices.size(), sf::PrimitiveType::TrianglesFan , states);

	if (_debugLinesEnabled && _vertices.size() > 0)
	{
		//we don't need the first and the last point. They are the center and the first point duplicated
		for (unsigned int i = 1; i < _vertices.size() - 1; ++i)
			Line{ sf::Vertex(getPosition(), _color), sf::Vertex(_vertices[i].position, _debugLineColor) }.draw(target, states);
	}
}

std::vector<sf::Vertex> seng::LightSource::calculatePolygonVertices(std::vector<Line> &lines)
{
	std::vector<sf::Vertex> vertices;
	std::vector<sf::Vector2f> uniquePoints;
	
	auto pos = getPosition();

	for (unsigned int i = 0; i < lines.size(); ++i)
	{
		uniquePoints.push_back(lines[i].a.position);
		uniquePoints.push_back(lines[i].b.position);
	}

	//remove all duplicated points
	uniquePoints.erase(
		std::unique(
			uniquePoints.begin(), 
			uniquePoints.end(),
			[](sf::Vector2f l, sf::Vector2f r) { return MathHelper::isZero(l.x - r.x) && MathHelper::isZero(l.y - r.y); }), 
		uniquePoints.end());

	for (auto &pt : uniquePoints)
	{
		//raycast to the point and get the closest intersection
		auto intersection = MathHelper::raycast(pos, pt, lines);
		vertices.push_back(sf::Vertex(intersection, _color));

		//calculate the angle of the ray
		auto angle = MathHelper::angle(pos, pt);

		//cast two more rays with a slightly offset angle (for corner cutting)
		auto x = cosf(angle + 0.0001f);
		auto y = sinf(angle + 0.0001f);
		intersection = MathHelper::raycast(pos, pos + sf::Vector2f(x, y), lines);
		vertices.push_back(sf::Vertex(intersection, _color));
			
		x = cosf(angle - 0.0001f);
		y = sinf(angle - 0.0001f);
		intersection = MathHelper::raycast(pos, pos + sf::Vector2f(x, y), lines);
		vertices.push_back(sf::Vertex(intersection, _color));
	}

	//sort intersections by angle so you can draw them as a trianglefan later (triangle fan: https://i.stack.imgur.com/fpSG5.png )
	std::sort(vertices.begin(), vertices.end(), [pos](const auto& lhs, const auto& rhs)
	{
		return MathHelper::angle(pos, lhs.position) < MathHelper::angle(pos, rhs.position);
	});

	//pushing first point to the back again and inserting center position at the beginning
	//looking at this graphic: https://i.stack.imgur.com/fpSG5.png
	//that will close the gap between "9" and "1"
	vertices.push_back(vertices[0]);
	vertices.insert(vertices.begin(), sf::Vertex(pos, _color));

	return vertices;
}