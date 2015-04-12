#pragma once
#include <SFML\Graphics.hpp>
#include <random>

#include "Grid.h"
#include "Food.h"
#include "Snake.h"
#include "EndGame.h"
#include "ScorePanel.h"

class World
{
public:
	World();
	sf::Vector2i window_size_snake() const;
	sf::Vector2i window_size() const;
	sf::Vector2i world_size() const;
	sf::Vector2i score_panel() const;
	float cell_size() const;
	float time() const;
	sf::Texture texture_food_();
	sf::Texture texture_fon_();
	sf::Texture texture_end_();
	sf::Font font_();
	std::mt19937 & rnd_gen();

	void draw_all(sf::RenderWindow &window) const;
	Food * get_food();
	Snake * get_snake();
	void update_all();
	void on_key_pressed(sf::Keyboard::Key code);


private:
	sf::Vector2i window_size_;
	sf::Vector2i world_size_;
	sf::Vector2i score_panel_;
	float cell_size_;
	sf::Texture texture_food;
	sf::Texture texture_fon;
	sf::Texture texture_end;
	sf::Font font;
private:
	sf::Clock clock_;
	std::random_device rd_;
	std::mt19937 gen_;
private:
	Grid grid_;
	Food food_;
	Snake snake_;
	ScorePanel score_panels_;
	EndGame endgame_;
};