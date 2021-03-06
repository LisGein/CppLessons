#include "EndGame.h"
#include "World.h"

EndGame::EndGame(World * world)
	: world_(world)
	, rect_(sf::Vector2f(world->window_size_snake()))
	, texture(world->texture_end_())
{
	rect_.setPosition(0, 0);
	rect_.setTexture(&texture);
};
void EndGame::draw(sf::RenderWindow &window) const
{
	window.draw(rect_);
}
