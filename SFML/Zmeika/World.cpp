#include "World.h"

World::World()
	: world_size_(40, 30)
	, cell_size_(20.f)
	, gen_(rd_())
	, grid_(this)
	, food_(this)
	, snake_(this)
{
}

sf::Vector2i World::window_size() const
{
	return world_size_ * static_cast<int>(ceil(cell_size_)); //cell - округление вверх
}

sf::Vector2i World::world_size() const
{
	return world_size_;
}

float World::cell_size() const
{
	return cell_size_;
}

float World::time() const
{
	return clock_.getElapsedTime().asSeconds();
}

std::mt19937 & World::rnd_gen()
{
	return gen_;
}

void World::draw_all(sf::RenderWindow &window) const
{
	food_.draw(window);
	grid_.draw(window);
	snake_.draw(window);

}

void World::on_key_pressed(sf::Keyboard::Key code, bool press)
{

}