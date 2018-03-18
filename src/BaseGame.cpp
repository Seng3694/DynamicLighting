#include "BaseGame.hpp"

BaseGame::BaseGame(const sf::VideoMode& videoMode, const sf::String& title)
{
	auto settings = sf::ContextSettings();
	settings.antialiasingLevel = 8;
	_window.create(videoMode, title, sf::Style::Default, settings);
}

void BaseGame::load()
{
	onLoad();
}

void BaseGame::update()
{
	auto elapsed = _clock.restart().asSeconds();
	
	sf::Event event;
	while (_window.pollEvent(event))
	{
		onHandleEvent(event);
		if (event.type == sf::Event::Closed)
			_window.close();
	}

	onUpdate(elapsed);
}

void BaseGame::draw()
{
	_window.clear(_clearColor);

	onDraw(_window);

	_window.display();
}

void BaseGame::unload()
{
	onUnload();
}

void BaseGame::setClearColor(const sf::Color &color)
{
	_clearColor = color;
}

bool BaseGame::isRunning()
{
	return _window.isOpen();
}

void BaseGame::exit()
{
	_window.close();
}