#include "Fon.h"
#include "World.h"

Fon::Fon(World * world)
	: world_(world)
	, pos_first(0, 0)
	, pos_second(1, 0)
{
	sf::Color first_color (42, 73, 47);
	sf::Color second_color(48, 84, 54);
	for (int i = 0; i < world->world_size().y; i++)
	{
		for (int i = 0; i < world->world_size().x ; i++)
		{
			fon_first.push_back(FonSegment(world, pos_first, first_color));
			pos_first.x += 1;
		}
		pos_first.x = 0;
		pos_first.y += 1;
	}
	for (int i = 0; i < world->world_size().y / 2; i++)
	{
		for (int i = 0; i < world->world_size().x / 2; i++)
		{			
			fon_second.push_back(FonSegment(world, pos_second, second_color));	
			pos_second.x += 2;
		}
		pos_second.x = 1;
		pos_second.y += 2;
	}
};

void Fon::draw(sf::RenderWindow &window) const
{
	for (size_t i = 0; i < fon_first.size(); i++)
	{
		window.draw(fon_first[i].rect_);
	}
	for (size_t i = 0; i < fon_second.size(); i++)
	{
		window.draw(fon_second[i].rect_);
	}
}

Fon::FonSegment::FonSegment(World * world, sf::Vector2i pos, sf::Color color)
	:rect_(sf::Vector2f(world->cell_size(), world->cell_size()))
	, pos_(pos)
	, color_(color)
{
	rect_.setPosition(pos_.x * world->cell_size(), pos_.y * world->cell_size());
	rect_.setFillColor(color);
}
	


