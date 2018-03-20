#include "CollidableShape.h"

CollidableShape::CollidableShape(sf::Shape* shape)
{
	_shape = shape;
}

void CollidableShape::reloadLines()
{
	_lines.clear();

	for (unsigned int i = 0; i < _shape->getPointCount(); ++i)
	{
		if (i + 1 < _shape->getPointCount())
			_lines.push_back(Line{ _shape->getPoint(i) + _shape->getPosition(), _shape->getPoint(i + 1) + _shape->getPosition(), _shape->getFillColor() });
		else
			_lines.push_back(Line{ _shape->getPoint(i) + _shape->getPosition(), _shape->getPoint(0) + _shape->getPosition(), _shape->getFillColor() });
	}
}

std::vector<Line> CollidableShape::getLines()
{
	return _lines;
}