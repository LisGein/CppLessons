#include "Shake.h"
#include "World.h"

Shake::Shake(World * world)
	:world_(world)
{

};
void Shake::set_random_pos()
{
	std::uniform_int_distribution<> x_coor(0, world_->world_size().x);
	std::uniform_int_distribution<> y_coor(0, world_->world_size().y);
	pos_ = sf::Vector2i(x_coor(world_->rnd_gen()), y_coor(world_->rnd_gen()));

	shake.setPosition(pos_.x * world_->cell_size(), pos_.y * world_->cell_size());
}
void Shake::draw(sf::RenderWindow &window) const
{
	window.draw(shake);
}
