#pragma once
#include <SFML\Graphics.hpp>
#include <random>

#include "Grid.h"
#include "Food.h"

class World
{
public:
	World();
	sf::Vector2i window_size() const;
	sf::Vector2i world_size() const;
	float cell_size() const;
	float time() const;
	std::mt19937 & rnd_gen();

	void draw_all(sf::RenderWindow &window) const;
	void on_key_pressed(sf::Keyboard::Key code, bool press);

private:
	sf::Vector2i window_size_;
	sf::Vector2i world_size_;
	float cell_size_;
private:
	sf::Clock clock_;
	std::random_device rd_;
	std::mt19937 gen_;
private:
	Grid grid_;
	Food food_;
};