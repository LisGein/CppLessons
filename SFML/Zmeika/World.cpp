#include "World.h"

World::World()
	: world_size_(40, 30)
	, cell_size_(20.f)
	, gen_(rd_())
	, grid_(this)
	, food_(this)
	, snake_(this)
	, endgame_(this)
	
{
}

sf::Vector2i World::window_size() const
{
	return world_size_ * static_cast<int>(ceil(cell_size_)); 
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

sf::Texture World::texture_food_()
{
	texture_food.loadFromFile("D:\\CppLessons\\SFML\\Zmeika\\Food.png");
	return texture_food;
}

sf::Texture World::texture_end_()
{
	texture_end.loadFromFile("D:\\CppLessons\\SFML\\Zmeika\\game.jpg");
	return texture_end;
}
std::mt19937 & World::rnd_gen()
{
	return gen_;
}

void World::draw_all(sf::RenderWindow &window) const
{
	if (snake_.is_alive())
	{
		grid_.draw(window);
		snake_.draw(window);
		food_.draw(window);
	}
	else
		endgame_.draw(window);

}

Food * World::get_food()
{
	return &food_;
}

void World::update_all()
{
	 snake_.update(time());
}

void World::on_key_pressed(sf::Keyboard::Key code)
{
	snake_.on_key_pressed(code);
}
