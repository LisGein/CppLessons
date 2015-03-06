#include <SFML/Graphics.hpp>
#include "World.h"

int main()
{
	World world;
	sf::RenderWindow window(sf::VideoMode(world.window_size().x, world.window_size().y), "SFML works!");
	window.setKeyRepeatEnabled(false);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				world.on_key_pressed(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				world.on_key_pressed(event.key.code, false);
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		window.clear();
		world.draw_all(window);
		window.display();
	}
	return 0;
}
