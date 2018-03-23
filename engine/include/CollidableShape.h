#pragma once

#include <SFML/Graphics.hpp>

#include "Line.h"

namespace seng
{
	class CollidableShape
	{
	public:
		CollidableShape(sf::Shape* shape);
		void reloadLines();
		std::vector<Line> getLines();

	private:
		sf::Shape* _shape;
		std::vector<Line> _lines;
	};
}