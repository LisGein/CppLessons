#pragma once
#include <SFML\Graphics.hpp>
#include <deque>
#include <iterator>
class World;

class Snake
{
private:
	struct SnakeSegment
	{
		SnakeSegment(sf::Vector2f pos_);
		sf::Vector2i pos;
		sf::RectangleShape rect;
		World * world_;
	};
	std::deque<SnakeSegment> snake;
public:
	Snake(World * world);
	void update(float dt);
	void draw(sf::RenderWindow &window) const;

private:
	World * world_;
	sf::Vector2f pos_;
	sf::Vector2f size_;
	sf::Vector2f speed_;
	float next_step;

};