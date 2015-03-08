#include "Food.h"
#include "World.h"


Food::Food(World * world) 
	: world_(world)
	, rect_(sf::Vector2f(world->cell_size(), world->cell_size())) //задаем размер еды
{
	std::uniform_int_distribution<> clr_dist(0, 255);
	sf::Color food_color(clr_dist(world_->rnd_gen()), clr_dist(world_->rnd_gen()), clr_dist(world_->rnd_gen()));
	rect_.setFillColor(food_color);// цвет еды

	set_random_pos();
};

void Food::set_random_pos()
{
	std::uniform_int_distribution<> x_coor(0, world_->world_size().x);
	std::uniform_int_distribution<> y_coor(0, world_->world_size().y);
	pos_ = sf::Vector2i(x_coor(world_->rnd_gen()), y_coor(world_->rnd_gen()));

	rect_.setPosition(pos_.x * world_->cell_size(), pos_.y * world_->cell_size());
}

void Food::draw(sf::RenderWindow &window) const
{
	window.draw(rect_);
}
