#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "BaseGame.hpp"
#include "CollidableShape.hpp"

class Game : public BaseGame
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
	std::vector<CollidableShape> _shapes;
	sf::CircleShape _bigCircle;
	sf::RectangleShape _border;
	sf::ConvexShape _polygon1;
	sf::ConvexShape _polygon2;
	std::vector<sf::CircleShape> _smallCircles;
};