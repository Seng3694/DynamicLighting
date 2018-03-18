#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Game.hpp"
#include "Colors.hpp"

Game::Game(const sf::VideoMode& videoMode, const sf::String& title)
	: BaseGame(videoMode, title)
{
}

void Game::onLoad()
{
	_random.setSeed(1337);
	setClearColor(Colors::DarkSlateBlue);

	_bigCircle.setPointCount(50);
	_bigCircle.setPosition(600, 300);
	_bigCircle.setRadius(100);
	_bigCircle.setFillColor(sf::Color::Red);

	_border.setSize(sf::Vector2f(_window.getSize()));
	_border.setFillColor(sf::Color::Transparent);
	
	_polygon1.setPointCount(4);
	_polygon1.setPoint(0, sf::Vector2f(10, 30));
	_polygon1.setPoint(1, sf::Vector2f(200, 10));
	_polygon1.setPoint(2, sf::Vector2f(170, 250));
	_polygon1.setPoint(3, sf::Vector2f(40, 80));
	_polygon1.setFillColor(sf::Color::Cyan);

	_polygon2.setPointCount(4);
	_polygon2.setPoint(0, sf::Vector2f(1100, 200));
	_polygon2.setPoint(1, sf::Vector2f(1300, 250));
	_polygon2.setPoint(2, sf::Vector2f(1500, 900));
	_polygon2.setPoint(3, sf::Vector2f(900, 650));
	_polygon2.setFillColor(sf::Color::Magenta);

	for (int i = 0; i < 10; i++)
	{
		auto circle = sf::CircleShape();
		circle.setPointCount(20);
		circle.setPosition(sf::Vector2f(100 + (i * 100), i % 2 == 0 ? 700 : 550));
		circle.setRadius(40);
		circle.setFillColor(sf::Color(_random.range(50, 255), _random.range(50, 255), _random.range(50, 255)));
		_smallCircles.push_back(circle);
	}

	_shapes.push_back(CollidableShape{ &_bigCircle });
	_shapes.push_back(CollidableShape{ &_border });
	_shapes.push_back(CollidableShape{ &_polygon1 });
	_shapes.push_back(CollidableShape{ &_polygon2 });

	for (auto &c : _smallCircles)
		_shapes.push_back(CollidableShape{ &c });

	for (auto &s : _shapes)
		s.reloadLines();

	_light.setColor(sf::Color(0xFFB200FF));
	_light.setDebugLineColor(sf::Color(0x999999FF));
	_light.setDebugLinesEnabled(true);

	_defaultFont.loadFromFile("content/fonts/boxy_bold.ttf");
	_fpsLabel.setFont(_defaultFont);
	_fpsLabel.setPosition(300, 10);
	_fpsLabel.setColor(sf::Color::Black);
}

void Game::onHandleEvent(const sf::Event& e)
{
	if (e.type == sf::Event::EventType::MouseMoved)
	{
		_light.setPosition(sf::Vector2f(e.mouseMove.x, e.mouseMove.y));
	}
}

void Game::onUpdate(float dt)
{
	_fpsCounter.update(dt);
	std::stringstream ss;
	ss << "Fps: " << _fpsCounter.getFps();
	_fpsLabel.setString(ss.str());

	_light.update(_shapes);
}

void Game::onDraw(sf::RenderTarget& target)
{
	target.draw(_bigCircle);
	target.draw(_border);
	target.draw(_polygon1);
	target.draw(_polygon2);

	for (auto &c : _smallCircles)
		target.draw(c);

	target.draw(_light);

	target.draw(_fpsLabel);
}

void Game::onUnload()
{

}