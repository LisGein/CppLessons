#pragma once
#include <SFML\Graphics.hpp>
#include <random>

#include "Fon.h"
#include "Grid.h"
#include "Food.h"
#include "Snake.h"
#include "EndGame.h"

class World
{
public:
	World();
	sf::Vector2i window_size() const;
	sf::Vector2i world_size() const;
	float cell_size() const;
	float time() const;
	sf::Texture texture_food_();
	sf::Texture texture_end_();
	std::mt19937 & rnd_gen();

	void draw_all(sf::RenderWindow &window) const;
	Food * get_food();
	void update_all();
	void on_key_pressed(sf::Keyboard::Key code);


private:
	sf::Vector2i window_size_;
	sf::Vector2i world_size_;
	float cell_size_;
	sf::Texture texture_food;
	sf::Texture texture_end;
private:
	sf::Clock clock_;
	std::random_device rd_;
	std::mt19937 gen_;
private:
	Fon fon_;
	Grid grid_;
	Food food_;
	Snake snake_;
	EndGame endgame_;
};