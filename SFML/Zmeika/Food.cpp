#include "Food.h"
#include "World.h"

Food::Food(World * world) 
	: world_(world)
	, rect_(sf::Vector2f(world->cell_size(), world->cell_size()))
	, texture_(world->texture_food_())
{
	
	std::uniform_int_distribution<> clr_dist(0, 255);
	sf::Color food_color(clr_dist(world_->rnd_gen()), clr_dist(world_->rnd_gen()), clr_dist(world_->rnd_gen()));
	color_ = food_color;
	rect_.setFillColor(color_);
	
	rect_.setTexture(&texture_);
	set_random_pos();
};

void Food::set_random_pos()
{
	std::uniform_int_distribution<> x_coor(0, world_->world_size().x - 1);
	std::uniform_int_distribution<> y_coor(0, world_->world_size().y - 1);
	pos_ = sf::Vector2i(x_coor(world_->rnd_gen()), y_coor(world_->rnd_gen()));

	rect_.setPosition(pos_.x * world_->cell_size() - 1, pos_.y * world_->cell_size() - 1);
}

sf::Vector2i Food::get_pos() const
{
	return pos_;
}

void Food::draw(sf::RenderWindow &window) const
{
	window.draw(rect_);
}
