#include "Gride.h"

Gride::Gride(sf::VertexArray const &line) :line_(line)
{
};

void Gride::draw(sf::RenderWindow &window)
{
	window.draw(line_);
}
