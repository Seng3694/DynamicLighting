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
	_isMouseDown = false;
	_showLights = true;

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

	_bigCircle.setPointCount(30);
	_bigCircle.setPosition(600, 350);
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

	for (int i = 0; i < 3; i++)
	{
		auto circle = sf::CircleShape();
		circle.setPointCount(15);
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

	for (int i = 0; i < 4; i++)
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
	_controlsText.setString("Key D => toggle debug lines\n\nKey L => toggle light\n\nscroll => change color\n\nmiddle mouse => set light\n\nleft mouse => draw line");
	_controlsText.setScale(0.8f, 0.8f);
}

void Game::onHandleEvent(const sf::Event& e)
{
	if (e.type == sf::Event::EventType::MouseMoved)
	{
		//moving light source cirles
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

		//add points for line drawing
		if (_isMouseDown)
		{
			_currentLineVectors.push_back(pos);
		}
	}
	if (e.type == sf::Event::EventType::MouseButtonPressed)
	{
		//start line drawing
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			_currentLineVectors.push_back(sf::Vector2f(e.mouseButton.x, e.mouseButton.y));
			_isMouseDown = true;
		}
	}
	if (e.type == sf::Event::EventType::MouseButtonReleased)
	{
		if (e.mouseButton.button == sf::Mouse::Middle)
		{
			//set current dynamic lights to static and create new dynamic lights
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
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			//end line drawing
			_currentLineVectors.push_back(sf::Vector2f(e.mouseButton.x, e.mouseButton.y));
			_isMouseDown = false;

			auto distance = 10.0f;

			//delete redundant points
			_currentLineVectors.erase(
				std::unique(
					_currentLineVectors.begin(),
					_currentLineVectors.end(),
					[distance](sf::Vector2f l, sf::Vector2f r) { return seng::MathHelper::magnitude(l, r) <= distance; }),
				_currentLineVectors.end());

			//create collidable lines
			for (unsigned int i = 0; i < _currentLineVectors.size(); ++i)
			{
				if (i + 1 < _currentLineVectors.size())
					_extraLines.push_back(seng::Line{ _currentLineVectors[i],_currentLineVectors[i + 1], sf::Color::Black });
			}

			_currentLineVectors.clear();

			//toggle static lights for one time recalculation
			for (auto &sl : _staticLights)
			{
				sl.setIsStatic(false);
				sl.setIsStatic(true);
			}
		}
	}
	if (e.type == sf::Event::MouseWheelScrolled)
	{
		//color change
		if (e.mouseWheelScroll.delta > 0) 
			_colorIndex = seng::MathHelper::circleClamp(_colorIndex + 1, 0, _colors.size() - 1);
		else if (e.mouseWheelScroll.delta < 0)
			_colorIndex = seng::MathHelper::circleClamp(_colorIndex -1, 0, _colors.size() - 1);

		for (auto &l : _dynamicLights)
		{
			l.setColor(_colors[_colorIndex]);
		}
	}
	if (e.type == sf::Event::EventType::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::D)
		{
			//toggle debugLines
			for (auto &l : _dynamicLights)
				l.setDebugLinesEnabled(!l.getDebugLinesEnabled());

			for (auto &l : _staticLights)
				l.setDebugLinesEnabled(!l.getDebugLinesEnabled());
		}
		if (e.key.code == sf::Keyboard::L)
		{
			//toggle light layer visibility
			_showLights = !_showLights;
		}
	}
}

void Game::onUpdate(float dt)
{
	_fpsCounter.update(dt);
	std::stringstream ss;
	ss << "Fps: " << _fpsCounter.getFps();
	_fpsLabel.setString(ss.str());

	std::vector<seng::Line> lines;

	for (auto &s : _shapes)
	{
		auto l = s.getLines();
		lines.insert(lines.end(), l.begin(), l.end());
	}

	lines.insert(lines.end(), _extraLines.begin(), _extraLines.end());
	
	for (auto &l : _staticLights)
		l.update(lines);

	for (auto &l : _dynamicLights)
		l.update(lines);
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

	if (_isMouseDown && _currentLineVectors.size() > 0)
	{
		std::vector<sf::Vertex> vertices;
		for (auto &v : _currentLineVectors)
			vertices.push_back(sf::Vertex(v, sf::Color::Black));

		_objectTexture.draw(&vertices[0], vertices.size(), sf::PrimitiveType::LinesStrip);
	}

	for (auto &l : _extraLines)
		_objectTexture.draw(l);

	if(_showLights)
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