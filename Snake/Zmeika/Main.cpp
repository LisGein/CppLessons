#include <SFML/Graphics.hpp>
#include "World.h"

int main()
{
	World world;
	sf::RenderWindow window(sf::VideoMode(world.window_size_snake().x, world.window_size_snake().y), "SFML works!");//
	window.setKeyRepeatEnabled(false);//проверка на нажатие клавиш. Стд:установленно

	while (window.isOpen())//пока окно открыто
	{
		sf::Event event; //подключение модуля события
		while (window.pollEvent(event))//проверка нажатия на кнопку закрытия экрана
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:  //выполнить если sf::Event::KeyPressed: == world.on_key_pressed(event.key.code, true);
				world.on_key_pressed(event.key.code);
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		world.update_all();

		window.clear();
		world.draw_all(window);
		window.display();
	}
	return 0;
}
