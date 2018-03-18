#include "LightSource.hpp"
#include "Math.hpp"
#include <set>
#include <algorithm>

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

void LightSource::update(std::vector<CollidableShape> &shapes)
{
	std::vector<Line> lines;

	for (auto &s : shapes)
	{
		auto l = s.getLines();
		lines.insert(lines.end(), l.begin(), l.end());
	}

	calculateRays(lines);
}

void LightSource::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (unsigned int i = 0; i < _rays.size(); i++)
	{
		auto polygon = sf::ConvexShape(3);
		polygon.setPoint(0, _rays[i].b.position);
		polygon.setPoint(1, _rays[i].a.position);

		if (i + 1 < _rays.size())
			polygon.setPoint(2, _rays[i + 1].b.position);
		else
			polygon.setPoint(2, _rays[0].b.position);

		polygon.setFillColor(_color);
		target.draw(polygon);

		if (_debugLinesEnabled)
			_rays[i].draw(target, states);
	}
}

void LightSource::calculateRays(std::vector<Line> &lines)
{
	std::vector<sf::Vector2f> intersections;
	std::vector<sf::Vector2f> uniquePoints;
	auto pos = getPosition();

	for (unsigned int i = 0; i < lines.size(); ++i)
	{
		uniquePoints.push_back(lines[i].a.position);
		uniquePoints.push_back(lines[i].b.position);
	}

	uniquePoints.erase(std::unique(uniquePoints.begin(), uniquePoints.end()), uniquePoints.end());

	for (auto &pt : uniquePoints)
	{
		auto ang = angle(pos, pt);
		auto intersection = raycast(pos, pt, lines);
		if (intersection.x != -1 || intersection.y != -1)
		{
			intersections.push_back(intersection);

			auto x = cosf(ang + 0.0001f);
			auto y = sinf(ang + 0.0001f);
			intersection = raycast(pos, pos + sf::Vector2f(x, y), lines);
			if (intersection.x != -1 || intersection.y != -1) 
				intersections.push_back(intersection);

			x = cosf(ang - 0.0001f);
			y = sinf(ang - 0.0001f);
			intersection = raycast(pos, pos + sf::Vector2f(x, y), lines);
			if (intersection.x != -1 || intersection.y != -1) 
				intersections.push_back(intersection);
		}
	}

	_rays.clear();
	
	for (auto &intersection : intersections)
		_rays.push_back(Line{ pos, intersection, _debugLineColor });

	std::sort(_rays.begin(), _rays.end(), [](const auto& lhs, const auto& rhs)
	{
		return angle(lhs) < angle(rhs);
	});
}