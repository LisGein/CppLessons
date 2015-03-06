#include "Grid.h"
#include "World.h"

Grid::Grid(World * world)
	: world_(world)
	, line_(sf::Lines)
{
	line_.resize(2 * (world_->world_size().x + world_->world_size().y));

	for (int i = 0; i < world_->world_size().x; i++)
	{
		float line_x = static_cast<float>(i * world_->cell_size());
		sf::Vector2f top_end(line_x, 0);
		sf::Vector2f bottom_end(line_x, static_cast<float>(world_->window_size().y));

		line_[2 * i].position = top_end;
		line_[2 * i + 1].position = bottom_end;
	}

	for (int i = 0; i < world_->world_size().y; i++)
	{
		float line_y = static_cast<float>(i * world_->cell_size());
		sf::Vector2f left_end(0, line_y);
		sf::Vector2f right_end(static_cast<float>(world_->window_size().x), line_y);

		line_[2 * world_->world_size().x + 2 * i].position = left_end;
		line_[2 * world_->world_size().x + 2 * i + 1].position = right_end;
	}
	
};

void Grid::draw(sf::RenderWindow &window) const
{
	window.draw(line_);
}
