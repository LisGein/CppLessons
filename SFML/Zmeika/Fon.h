#pragma once
#include <SFML/Graphics.hpp>
class World;

class Fon
{
private:
	struct FonSegment
	{
		FonSegment(World * world, sf::Vector2i pos, sf::Color color);
		World * world_;
		sf::Vector2i pos_;
		sf::RectangleShape rect_;
		sf::Color color_;
	};
	std::vector<FonSegment> fon_first;
	std::vector<FonSegment> fon_second;
public:
	Fon(World * world);
	void draw(sf::RenderWindow &window) const;

private:
	World * world_;
	sf::Vector2i pos_first;
	sf::Vector2i pos_second;
};