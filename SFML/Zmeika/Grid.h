#pragma once
#include <SFML/Graphics.hpp>

class World; //forward declaration

class Grid
{
public:
	Grid(World * world);
	void draw(sf::RenderWindow &window) const;
private:
	World * world_;
	sf::VertexArray line_;
};
