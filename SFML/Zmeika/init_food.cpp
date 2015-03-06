#include "init_food.h"
#include "global.h"

void init_food(std::vector<Food> &rect, std::mt19937 &gen)  //определение всех переменных для мячей
{
	sf::Vector2f size(30, 30);
	std::uniform_int_distribution<> x_coor(0, WINDOW_WIDTH / size.x - stdpix);
	std::uniform_int_distribution<> y_coor(0, WINDOW_HEIGHT / size.y - stdpix);
	sf::Vector2i pos((x_coor(gen) * size.x), (y_coor(gen) * size.y));
	sf::Vector2f pos_(static_cast<float> (pos.x), static_cast<float> (pos.y));
	std::uniform_int_distribution<> color_dist(0, 255);
	sf::Color color(color_dist(gen), color_dist(gen), color_dist(gen));
	sf::VertexArray obj(sf::Quads, 4);
	obj[0].position = pos_;
	int pos_save = pos_.x;
	pos_.x += size.x;
	obj[1].position = pos_;
	pos_.y += size.y;
	obj[2].position = pos_;
	pos_.x = pos_save;
	obj[3].position = pos_;
	obj[0].color = color;
	obj[1].color = color;
	obj[2].color = color;
	obj[3].color = color;
	rect.push_back(Food(obj));
}