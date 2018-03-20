#include <algorithm>

#include "LightSource.hpp"
#include "Math.hpp"

LightSource::LightSource()
	: _debugLineColor(sf::Color::Red), _color(sf::Color::Yellow)
{
}

void LightSource::setColor(const sf::Color& color)
{
	_color = color;
}

sf::Color LightSource::getColor() const
{
	return _color;
}

void LightSource::setDebugLineColor(const sf::Color& color)
{
	_debugLineColor = color;
}

sf::Color LightSource::getDebugLineColor() const
{
	return _debugLineColor;
}

void LightSource::setDebugLinesEnabled(const bool& value)
{
	_debugLinesEnabled = value;
}

bool LightSource::getDebugLinesEnabled() const
{
	return _debugLinesEnabled;
}

void LightSource::setIsStatic(const bool& value)
{
	if (value && !_isStatic)
	{
		_staticAfterUpdate = true;
	}
	else if (!value)
	{
		_isStatic = value;
		_staticAfterUpdate = false;
	}
}

bool LightSource::getIsStatic() const
{
	return _isStatic;
}

void LightSource::update(std::vector<CollidableShape> &shapes)
{
	if (_isStatic)
	{
		std::vector<Line> lines;

		for (auto &s : shapes)
		{
			auto l = s.getLines();
			lines.insert(lines.end(), l.begin(), l.end());
		}

		_vertices = calculatePolygonVertices(lines);

		if (_staticAfterUpdate)
		{
			_isStatic = true;
			_staticAfterUpdate = false;
		}
	}
}

void LightSource::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(&_vertices[0], _vertices.size(), sf::PrimitiveType::TriangleFan, states);

	if (_debugLinesEnabled && _vertices.size() > 0)
	{
		for (auto &it = _vertices.begin() + 1; it < _vertices.end() - 1; ++it)
			Line{ sf::Vertex(getPosition(), _color), sf::Vertex(it->position, _debugLineColor) }.draw(target, states);
	}
}

std::vector<sf::Vertex> LightSource::calculatePolygonVertices(std::vector<Line> &lines)
{
	std::vector<sf::Vertex> vertices;
	std::vector<sf::Vector2f> uniquePoints;
	auto pos = getPosition();

	for (unsigned int i = 0; i < lines.size(); ++i)
	{
		uniquePoints.push_back(lines[i].a.position);
		uniquePoints.push_back(lines[i].b.position);
	}

	uniquePoints.erase(
		std::unique(
			uniquePoints.begin(), 
			uniquePoints.end(),
			[](sf::Vector2f l, sf::Vector2f r) { return std::abs(l.x - r.x) < 0.001 && std::abs(l.y - r.y) < 0.001; }), 
		uniquePoints.end());

	for (auto &pt : uniquePoints)
	{
		auto ang = angle(pos, pt);
		auto intersection = raycast(pos, pt, lines);

		vertices.push_back(sf::Vertex(intersection, _color));

		auto x = cosf(ang + 0.0001f);
		auto y = sinf(ang + 0.0001f);
		intersection = raycast(pos, pos + sf::Vector2f(x, y), lines);
		vertices.push_back(sf::Vertex(intersection, _color));
			
		x = cosf(ang - 0.0001f);
		y = sinf(ang - 0.0001f);
		intersection = raycast(pos, pos + sf::Vector2f(x, y), lines);
		vertices.push_back(sf::Vertex(intersection, _color));
	}

	std::sort(vertices.begin(), vertices.end(), [pos](const auto& lhs, const auto& rhs)
	{
		return angle(pos, lhs.position) < angle(pos, rhs.position);
	});

	vertices.push_back(vertices[0]);
	vertices.insert(vertices.begin(), sf::Vertex(pos, _color));

	return vertices;
}