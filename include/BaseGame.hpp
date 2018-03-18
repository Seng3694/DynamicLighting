#pragma once

#include <SFML/Graphics.hpp>

#include "Random.hpp"

class BaseGame
{
public:
	BaseGame(const sf::VideoMode& videoMode, const sf::String& title);
	virtual ~BaseGame() { };

	void load();
	void update();
	void draw();
	void unload();

	bool isRunning();

protected:
	sf::RenderWindow _window;
	Random _random;

	virtual void onLoad() = 0;
	virtual void onHandleEvent(const sf::Event& e) = 0;
	virtual void onUpdate(float dt) = 0;
	virtual void onDraw(sf::RenderTarget& target) = 0;
	virtual void onUnload() = 0;

	void setClearColor(const sf::Color &color);
	void exit();

private:
	sf::Color _clearColor;
	sf::Clock _clock;
	bool _shouldExit;
};