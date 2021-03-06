#include "World.h"

World::World()
	: world_size_(40, 30)
	, score_panel_(7, 0)
	, cell_size_(20.f)
	, gen_(rd_())
	, grid_(this)
	, food_(this)
	, snake_(this)
	, score_panels_(this)
	, endgame_(this)	
{
}
sf::Vector2i World::score_panel() const
{
	return score_panel_;
}
sf::Vector2i World::window_size_snake() const
{
	return world_size_ * static_cast<int>(ceil(cell_size_)) + score_panel_ * static_cast<int>(ceil(cell_size_));
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
	texture_food.loadFromFile("Food.png");
	return texture_food;
}
sf::Texture World::texture_fon_()
{
	texture_fon.loadFromFile("fon.jpeg");
	return texture_fon;
}
sf::Texture World::texture_end_()
{
	texture_end.loadFromFile("game.png");
	return texture_end;
}
sf::Font World::font_()
{
	font.loadFromFile("Font.ttf");
	return font;
}
std::mt19937 & World::rnd_gen()
{
	return gen_;
}

Food * World::get_food()
{
	return &food_;
}

Snake * World::get_snake()
{
	return &snake_;
}

void World::draw_all(sf::RenderWindow &window) const
{
	if (snake_.is_alive())
	{
		grid_.draw(window);
		snake_.draw(window);
		food_.draw(window);
		score_panels_.draw(window);
	}
	else
		endgame_.draw(window);
}

void World::update_all()
{
	 snake_.update(time());
	 score_panels_.update_score();
}

void World::on_key_pressed(sf::Keyboard::Key code)
{
	snake_.on_key_pressed(code);
}
