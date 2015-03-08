#pragma once
#include <SFML\Graphics.hpp>
#include <queue>
class World;

class Shake
{
public:
	Shake(World * world);
	void draw(sf::RenderWindow &window) const;
	void set_random_pos();
private:
	World * world_;
	sf::Vector2i pos_;
	std::queue<sf::Vector2i> shake_;
	sf::RectangleShape shake;

};