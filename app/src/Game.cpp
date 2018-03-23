#include <sstream>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "MathHelper.h"

#include "Game.h"
#include "Colors.h"

#define PI 3.14159265358979323846f

Game::Game(const sf::VideoMode& videoMode, const sf::String& title)
	: seng::BaseGame(videoMode, title)
{
}

void Game::onLoad()
{
	setClearColor(sf::Color::White);
	_window.setMouseCursorVisible(false);
	_ambientColor = sf::Color(10, 10, 10);
	_colors.push_back(Colors::DeepCobaltBlue);
	_colors.push_back(Colors::DeepFuchsia);
	_colors.push_back(Colors::Burgundy);
	_colors.push_back(Colors::Crimson);
	_colors.push_back(Colors::OutrageousOrange);
	_colors.push_back(Colors::GoldenPoppy);

	for (auto &c : _colors)
	{
		c.r *= 0.2f;
		c.g *= 0.2f;
		c.b *= 0.2f;
	}

	_colorIndex = 0;

	_lightTexture.create(_window.getSize().x, _window.getSize().y);
	_lightTexture.setSmooth(true);

	_objectTexture.create(_window.getSize().x, _window.getSize().y);
	_objectTexture.setSmooth(true);

	_bigCircle.setPointCount(40);
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

	for (int i = 0; i < 5; i++)
	{
		auto circle = sf::CircleShape();
		circle.setPointCount(20);
		circle.setPosition(sf::Vector2f(100 + (i * 100), i % 2 == 0 ? 700 : 550));
		circle.setRadius(20);
		circle.setFillColor(sf::Color(_random.range(50, 255), _random.range(50, 255), _random.range(50, 255)));
		_smallCircles.push_back(circle);
	}

	_shapes.push_back(seng::CollidableShape{ &_bigCircle });
	_shapes.push_back(seng::CollidableShape{ &_border });
	_shapes.push_back(seng::CollidableShape{ &_polygon1 });
	_shapes.push_back(seng::CollidableShape{ &_polygon2 });

	for (auto &c : _smallCircles)
		_shapes.push_back(seng::CollidableShape{ &c });

	for (auto &s : _shapes)
		s.reloadLines();

	for (int i = 0; i < 8; i++)
	{
		auto light = seng::LightSource();

		light.setColor(_colors[_colorIndex]);
		light.setDebugLineColor(sf::Color(0x000000FF));
		light.setDebugLinesEnabled(true);

		_dynamicLights.push_back(light);

		auto shape = sf::CircleShape();
		shape.setFillColor(_colors[_colorIndex]);
		shape.setRadius(5);
		shape.setOrigin(5, 5);
		shape.setPointCount(5);
		_lightSourceCircles.push_back(shape);
	}
	_radius = 15;

	_defaultFont.loadFromFile("content/fonts/boxy_bold.ttf");
	_fpsLabel.setFont(_defaultFont);
	_fpsLabel.setPosition(300, 10);
	_fpsLabel.setColor(sf::Color::Black);
	_controlsText.setFont(_defaultFont);
	_controlsText.setPosition(300, 70);
	_controlsText.setColor(sf::Color::Black);
	_controlsText.setString("Key D => toggle debug lines\n\nscroll => change color\n\nleft mouse => set light");
	_controlsText.setScale(0.8f, 0.8f);
}

void Game::onHandleEvent(const sf::Event& e)
{
	if (e.type == sf::Event::EventType::MouseMoved)
	{
		auto radians = (2 * PI) / _dynamicLights.size();
		auto pos = sf::Vector2f(e.mouseMove.x, e.mouseMove.y);

		for (unsigned int i = 0; i < _dynamicLights.size(); i++)
		{
			auto x = cosf(radians * i);
			auto y = sinf(radians * i);
			auto vec = sf::Vector2f(x, y) * _radius;

			_dynamicLights[i].setPosition(pos + vec);
			_lightSourceCircles[i].setPosition(pos + vec);
		}
	}
	if (e.type == sf::Event::EventType::MouseButtonReleased)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			for (auto &l : _dynamicLights)
			{
				l.setIsStatic(true);
				_staticLights.push_back(l);

				l = seng::LightSource();
				l.setColor(_colors[_colorIndex]);
				l.setDebugLineColor(sf::Color(0x000000FF));
				l.setDebugLinesEnabled(_staticLights.back().getDebugLinesEnabled());
			}
		}
	}
	if (e.type == sf::Event::MouseWheelScrolled)
	{
		if (e.mouseWheelScroll.delta > 0) 
			_colorIndex = seng::MathHelper::circle(_colorIndex + 1, 0, _colors.size() - 1);
		else if (e.mouseWheelScroll.delta < 0)
			_colorIndex = seng::MathHelper::circle(_colorIndex -1, 0, _colors.size() - 1);

		for (auto &l : _dynamicLights)
		{
			l.setColor(_colors[_colorIndex]);
		}
	}
	if (e.type == sf::Event::EventType::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::D)
		{
			for (auto &l : _dynamicLights)
				l.setDebugLinesEnabled(!l.getDebugLinesEnabled());

			for (auto &l : _staticLights)
				l.setDebugLinesEnabled(!l.getDebugLinesEnabled());
		}
	}
}

void Game::onUpdate(float dt)
{
	_fpsCounter.update(dt);
	std::stringstream ss;
	ss << "Fps: " << _fpsCounter.getFps();
	_fpsLabel.setString(ss.str());

	for (auto &l : _dynamicLights)
		l.update(_shapes);
}

void Game::onDraw(sf::RenderTarget& target)
{
	target.clear(sf::Color::White);

	_lightTexture.clear(_ambientColor);

	for (auto &l : _staticLights)
		_lightTexture.draw(l, sf::BlendAdd);

	for (auto &l : _dynamicLights)
		_lightTexture.draw(l, sf::BlendAdd);

	_lightTexture.display();

	_objectTexture.clear(sf::Color::White);

	_objectTexture.draw(_bigCircle);
	_objectTexture.draw(_border);
	_objectTexture.draw(_polygon1);
	_objectTexture.draw(_polygon2);

	for (auto &c : _smallCircles)
		_objectTexture.draw(c);

	_objectTexture.draw(sf::Sprite(_lightTexture.getTexture()), sf::BlendMultiply);
	_objectTexture.display();

	target.draw(sf::Sprite(_objectTexture.getTexture()));


	for (auto &s : _lightSourceCircles)
		target.draw(s);

	target.draw(_fpsLabel);
	target.draw(_controlsText);
}

void Game::onUnload()
{
}