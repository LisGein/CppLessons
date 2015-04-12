#pragma once
#include <SFML/Graphics.hpp>
class World;

class EndGame
{
public:
	EndGame(World * world);
	void draw(sf::RenderWindow &window) const;
private:
	World * world_;
	sf::Vector2i pos_;
	sf::RectangleShape rect_;
	sf::Texture texture;
	sf::Color color_;
};
