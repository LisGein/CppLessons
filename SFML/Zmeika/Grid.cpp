#include "Grid.h"
#include "World.h"

Grid::Grid(World * world)
	: world_(world)
	, lines_(sf::Lines)
	, pos_first_color(0, 0)
	, pos_second_color(1, 0)
{
	lines_.resize(2 * (world_->world_size().x + world_->world_size().y));
	sf::Color first_color(42, 73, 47);
	sf::Color second_color(48, 84, 54);

	for (int i = 0; i < world_->world_size().x; i ++)
	{
		float line_x = static_cast<float>(i * world_->cell_size());
		sf::Vector2f top_end(line_x, 0);
		sf::Vector2f bottom_end(line_x, static_cast<float>(world_->window_size_snake().y));

		lines_[2 * i].position = top_end;
		lines_[2 * i + 1].position = bottom_end;
	}

	for (int i = 0; i < world_->world_size().y; i ++)
	{
		float line_y = static_cast<float>(i * world_->cell_size());
		sf::Vector2f left_end(0, line_y);
		sf::Vector2f right_end(static_cast<float>(world_->window_size_snake().x - world_->score_panel().x * world_->cell_size()), line_y);

		lines_[2 * world_->world_size().x + 2 * i].position = left_end;
		lines_[2 * world_->world_size().x + 2 * i + 1].position = right_end;
	}

	for (int i = 0; i < world->world_size().y; i++)
	{
		for (int i = 0; i < world->world_size().x; i++)
		{
			fon_first.push_back(FonSegment(world, pos_first_color, first_color));
			pos_first_color.x += 1;
		}
		pos_first_color.x = 0;
		pos_first_color.y += 1;
	}
	for (int i = 0; i < world->world_size().y / 2; i++)
	{
		for (int i = 0; i < world->world_size().x / 2; i++)
		{
			fon_second.push_back(FonSegment(world, pos_second_color, second_color));
			pos_second_color.x += 2;
		}
		pos_second_color.x = 1;
		pos_second_color.y += 2;
	}	
};

void Grid::draw(sf::RenderWindow &window) const
{
	
	for (size_t i = 0; i < fon_first.size(); i++)
	{
		window.draw(fon_first[i].rect_);
	}
	for (size_t i = 0; i < fon_second.size(); i++)
	{
		window.draw(fon_second[i].rect_);
	}
	window.draw(lines_);
}
Grid::FonSegment::FonSegment(World * world, sf::Vector2i pos, sf::Color color)
	:rect_(sf::Vector2f(world->cell_size(), world->cell_size()))
	, pos_(pos)
	, color_(color)
{
	rect_.setPosition(pos_.x * world->cell_size(), pos_.y * world->cell_size());
	rect_.setFillColor(color);
}