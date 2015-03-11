#include "Fon.h"
#include "World.h"

Fon::Fon(World * world)
	: world_(world)
	
	, rect_(sf::Vector2f(world->window_size()))
{
	sf::Color fon_color(0, 102, 0);
	rect_.setFillColor(fon_color);
};

void Fon::draw(sf::RenderWindow &window) const
{
	window.draw(rect_);
}
