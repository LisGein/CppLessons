#include "EndGame.h"
#include "World.h"


EndGame::EndGame(World * world)
	: world_(world)
	, texture(world->texture_end_())
{
	rect_.setPosition(0, 0);
	rect_.setTexture(&texture);
};


void EndGame::draw(sf::RenderWindow &window) const
{
	window.draw(rect_);
}
