#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "BaseGame.h"
#include "FpsCounter.h"
#include "LightSource.h"
#include "CollidableShape.h"

class Game : public seng::BaseGame
{
public:
	Game(const sf::VideoMode& videoMode, const sf::String& title);

protected:
	virtual void onLoad() override;
	virtual void onHandleEvent(const sf::Event& e) override;
	virtual void onUpdate(float dt) override;
	virtual void onDraw(sf::RenderTarget& target) override;
	virtual void onUnload() override;

private:
	std::vector<seng::CollidableShape> _shapes;
	sf::CircleShape _bigCircle;
	sf::RectangleShape _border;
	sf::ConvexShape _polygon1;
	sf::ConvexShape _polygon2;
	std::vector<sf::CircleShape> _smallCircles;
	sf::Font _defaultFont;
	seng::FpsCounter _fpsCounter;
	sf::Text _fpsLabel;
	sf::Text _controlsText;
	std::vector<seng::LightSource> _staticLights;
	std::vector<seng::LightSource> _dynamicLights;
	std::vector<sf::CircleShape> _lightSourceCircles;
	float _radius;
	sf::RenderTexture _lightTexture;
	sf::RenderTexture _objectTexture;
	sf::Color _ambientColor;
	int _colorIndex;
	std::vector<sf::Color> _colors;
};