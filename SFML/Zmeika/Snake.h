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
		SnakeSegment(World * world, sf::Vector2i pos);
		World * world_;
		sf::Vector2i pos_;
		sf::RectangleShape rect_;		
	};
	std::deque<SnakeSegment> snake_;
public:
	Snake(World * world);
	void update(float time_);
	bool is_alive() const;
	void draw(sf::RenderWindow &window) const;
	void on_key_pressed(sf::Keyboard::Key code);

private:
	World * world_;
	sf::Vector2i pos_;
	sf::Vector2i speed_;
	float pres_step_;
	int size_;
	sf::Vector2f pos_head;
	sf::Vector2f pos_next;
	bool alive_;
};