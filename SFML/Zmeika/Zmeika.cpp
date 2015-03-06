#include <SFML/Graphics.hpp>
#include "global.h"
#include <vector>
#include <Random>
#include "Gride.h"
#include "Food.h"
#include "init_gride.h"
#include "init_food.h"
#include "draw_all.h"

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
int main()
{
	std::vector<Gride> lines;
	std::vector<Food> rect;
	sf::Clock clock;
	std::random_device rd;
	std::mt19937 gen(rd());
	bool press = false;
	init_gride(lines);
	init_food(rect, gen);

	float last_up = clock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
				press = true;
			if (event.type == sf::Event::KeyReleased)
				press = false;



			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		draw_all(lines, rect);
		window.display();
	}
	return 0;
}
