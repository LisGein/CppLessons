#pragma once
#include <SFML/Graphics.hpp>
class World;

class Fon
{
public:
	Fon(World * world);
	void draw(sf::RenderWindow &window) const;

private:
	World * world_;
	sf::Vector2i pos_;
	sf::RectangleShape rect_;
	sf::Vector2i size_fon;
};