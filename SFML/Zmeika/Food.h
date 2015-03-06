#include <SFML/Graphics.hpp>
#ifndef __FOOD_H__
#define __FOOD_H__
class Food
{
public:
	Food(sf::VertexArray const &rect);
	void draw(sf::RenderWindow &window);
private:
	sf::VertexArray rect_;
};
#endif