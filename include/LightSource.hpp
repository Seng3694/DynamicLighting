#pragma once

#include <SFML/Graphics.hpp>

class LightSource : sf::Drawable, sf::Transformable
{
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};