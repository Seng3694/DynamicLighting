#include "Game.hpp"
#include "CollidableShape.hpp"
#include <SFML/Graphics.hpp>

int main()
{
	Game game(sf::VideoMode{1600, 1000}, "lighting");
	
	game.load();

	while (game.isRunning())
	{
		game.update();
		game.draw();
	}
	
	game.unload();

    return 0;
}