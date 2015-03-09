#include "Snake.h"
#include "World.h"

Snake::Snake(World * world)
	: world_(world)
	, size_(world_->cell_size(), world_->cell_size())
	, speed_(1, 0)
	, next_step(0)
	, pos_(world_->cell_size(), world_->cell_size())
{
	snake_.push_back(pos_);
};

Snake::SnakeSegment::SnakeSegment(sf::Vector2f pos_)
:rect_(sf::Vector2f(world_->cell_size(), world_->cell_size()))
	{
		rect_.setPosition(pos.x * world_->cell_size(), pos.y * world_->cell_size());
	}


void Snake::update(World * world, float dt)
{
	next_step = next_step + dt;
	if (next_step >= 0.7)
	{
		if (pos_.y > world_->world_size().x / world_->cell_size() - 2)
			speed_ = sf::Vector2f(speed_.x, -abs(speed_.y));//пол		
		if (pos_.x > world_->world_size().y / world_->cell_size() - 2)
			speed_ = sf::Vector2f(-abs(speed_.x), speed_.y);//право
		if (pos_.y < 1) //потолок
			speed_ = sf::Vector2f(speed_.x, abs(speed_.y));
		if (pos_.x < 1) //лево
			speed_ = sf::Vector2f(abs(speed_.x), speed_.y);
		pos_ += speed_;
		next_step = 0;
		snake_.push_back(pos_);
		//snake_.pop_front();
	}
}
void Snake::draw(sf::RenderWindow &window) const
{
	for (int i = 0; i < snake_.size(); i++)
	{
		window.draw(snake_[i].rect_);
	}
}


