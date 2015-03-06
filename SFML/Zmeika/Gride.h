#include <SFML/Graphics.hpp>
#ifndef __GRIDE_H__
#define __GRIDE_H__
class Gride
{
public:
	Gride(sf::VertexArray const &line);
	void draw(sf::RenderWindow &window);
private:
	sf::VertexArray line_;
};
#endif