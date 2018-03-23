#include "BaseGame.h"

seng::BaseGame::BaseGame(const sf::VideoMode& videoMode, const sf::String& title)
{
	auto settings = sf::ContextSettings();
	settings.antialiasingLevel = 8;
	_window.create(videoMode, title, sf::Style::Default, settings);
}

void seng::BaseGame::load()
{
	onLoad();
}

void seng::BaseGame::update()
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

void seng::BaseGame::draw()
{
	_window.clear(_clearColor);

	onDraw(_window);

	_window.display();
}

void seng::BaseGame::unload()
{
	onUnload();
}

void seng::BaseGame::setClearColor(const sf::Color &color)
{
	_clearColor = color;
}

bool seng::BaseGame::isRunning()
{
	return _window.isOpen();
}

void seng::BaseGame::exit()
{
	_window.close();
}