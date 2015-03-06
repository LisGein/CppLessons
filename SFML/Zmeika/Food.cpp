#include "Food.h"


Food::Food(sf::VertexArray const &rect) :rect_(rect)
{
};

void Food::draw(sf::RenderWindow &window)
{
	window.draw(rect_);
}
