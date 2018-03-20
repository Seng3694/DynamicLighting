#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Game.h"
#include "Colors.h"
#include "CustomMath.h"

Game::Game(const sf::VideoMode& videoMode, const sf::String& title)
	: BaseGame(videoMode, title)
{
}

void Game::onLoad()
{
	setClearColor(sf::Color::White);
	_ambientColor = sf::Color(10, 10, 10);
	_colors.push_back(Colors::DeepCobaltBlue);
	_colors.push_back(Colors::DeepFuchsia);
	_colors.push_back(Colors::Burgundy);
	_colors.push_back(Colors::Crimson);
	_colors.push_back(Colors::OutrageousOrange);
	_colors.push_back(Colors::GoldenPoppy);
	_colorIndex = 0;

	_lightTexture.create(_window.getSize().x, _window.getSize().y);
	_lightTexture.setSmooth(true);

	_objectTexture.create(_window.getSize().x, _window.getSize().y);
	_objectTexture.setSmooth(true);

	_bigCircle.setPointCount(30);
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
		circle.setPointCount(10);
		circle.setPosition(sf::Vector2f(100 + (i * 100), i % 2 == 0 ? 700 : 550));
		circle.setRadius(20);
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

	_light.setColor(_colors[_colorIndex]);
	_light.setDebugLineColor(sf::Color(0x000000FF));
	_light.setDebugLinesEnabled(true);

	_defaultFont.loadFromFile("content/fonts/boxy_bold.ttf");
	_fpsLabel.setFont(_defaultFont);
	_fpsLabel.setPosition(300, 10);
	_fpsLabel.setFillColor(sf::Color::Black);
	_controlsText.setFont(_defaultFont);
	_controlsText.setPosition(300, 70);
	_controlsText.setFillColor(sf::Color::Black);
	_controlsText.setString("Key D => toggle debug lines\n\nscroll => change color\n\nleft mouse => set light");
	_controlsText.setScale(0.8f, 0.8f);
}

void Game::onHandleEvent(const sf::Event& e)
{
	if (e.type == sf::Event::EventType::MouseMoved)
	{
		_light.setPosition(sf::Vector2f(e.mouseMove.x, e.mouseMove.y));
	}
	if (e.type == sf::Event::EventType::MouseButtonReleased)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			_light.setIsStatic(true);
			_staticLights.push_back(_light);

			_light = LightSource{};
			_light.setColor(_colors[_colorIndex]);
			_light.setDebugLineColor(sf::Color(0x000000FF));
			_light.setDebugLinesEnabled(_staticLights.back().getDebugLinesEnabled());
		}
	}
	if (e.type == sf::Event::MouseWheelScrolled)
	{
		if (e.mouseWheelScroll.delta > 0) 
			_colorIndex = circle(_colorIndex + 1, 0, _colors.size() - 1);
		else if (e.mouseWheelScroll.delta < 0)
			_colorIndex = circle(_colorIndex -1, 0, _colors.size() - 1);

		_light.setColor(_colors[_colorIndex]);
	}
	if (e.type == sf::Event::EventType::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::D)
		{
			_light.setDebugLinesEnabled(!_light.getDebugLinesEnabled());

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

	_light.update(_shapes);
}

void Game::onDraw(sf::RenderTarget& target)
{
	target.clear(sf::Color::White);

	_lightTexture.clear(_ambientColor);

	for (auto &l : _staticLights)
		_lightTexture.draw(l, sf::BlendAdd);

	_lightTexture.draw(_light, sf::BlendAdd);
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
	target.draw(_fpsLabel);
	target.draw(_controlsText);
}

void Game::onUnload()
{
}