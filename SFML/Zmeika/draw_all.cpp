#include <SFML/Graphics.hpp>
#include "draw_all.h"
#include "global.h"

void draw_all(std::vector<Gride> &lines, std::vector<Food> &rect)
{
	for (int i = 0; i < lines.size(); ++i)
		lines[i].draw(window);
	for (int i = 0; i < rect.size(); ++i)
		rect[i].draw(window);
}