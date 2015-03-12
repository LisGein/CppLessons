#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
class World;

class ScorePanel
{
public:
	ScorePanel(World * world);
	void update_score();
	void draw(sf::RenderWindow &window) const;
private:
	World * world_;
	sf::Text text_score;
	sf::Font font_score;
	sf::RectangleShape rect_;
	std::ostringstream input_;
	int score_input;
};
