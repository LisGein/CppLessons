#include "Snake.h"
#include "World.h"
#include <iostream>

Snake::Snake(World * world)
	: speed_(1, 0)
	, pres_step_(0)
	, pos_(0, 0)
	, world_(world)
	, size_(5)
	, alive_(true)
	, score_(0)
{
	snake_.push_back(SnakeSegment(world, pos_));
};

Snake::SnakeSegment::SnakeSegment(World * world, sf::Vector2i pos)
	:rect_(sf::Vector2f(world->cell_size(), world->cell_size()))
	,pos_(pos)
{
	rect_.setPosition(pos_.x * world->cell_size(), pos_.y * world->cell_size());
}

void Snake::update(float time)
{
	if (time - pres_step_ >= 0.2)
	{
		pos_ += speed_;
		if (pos_.y > world_->world_size().y - 1)
			pos_.y = 0;
		if (pos_.x > world_->world_size().x - 1)
			pos_.x = 0;
		if (pos_.y < 0) //потолок
			pos_.y = world_->world_size().y;
		if (pos_.x < 0) //лево
			pos_.x = world_->world_size().x;

		pres_step_ = time;
		snake_.push_back(SnakeSegment(world_, pos_));
		if (world_->get_food()->get_pos() == pos_)
		{
			size_ += 3;
			score_ += 1;
			world_->get_food()->set_random_pos();
		}
		if (snake_.size() > size_)
			snake_.pop_front();
		for (int i = 0; i < snake_.size() - 1; i++)
		{
			if (snake_.back().pos_ == snake_[i].pos_)
				alive_ = false;
		}
	}
}

bool Snake::is_alive() const
{
	return alive_;
}

void Snake::draw(sf::RenderWindow &window) const
{
	for (size_t i = 0; i < snake_.size(); i++)
	{
		window.draw(snake_[i].rect_);
	}
}

void Snake::on_key_pressed(sf::Keyboard::Key code)
{
	if (code == sf::Keyboard::Up)
		speed_ = sf::Vector2i(0, -1);
	if (code == sf::Keyboard::Down)
		speed_ = sf::Vector2i(0, 1);
	if (code == sf::Keyboard::Right)
		speed_ = sf::Vector2i(1, 0);
	if (code == sf::Keyboard::Left)
		speed_ = sf::Vector2i(-1, 0);
}

int Snake::get_score() const
{
	return score_;
}