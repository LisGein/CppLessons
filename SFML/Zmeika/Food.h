#pragma once
#include <SFML/Graphics.hpp>
class World;

class Food
{
public:
	Food(World * world);
	void draw(sf::RenderWindow &window) const;
	void set_random_pos();

private:
	World * world_;
	sf::Vector2i pos_;
	sf::RectangleShape rect_;
};
