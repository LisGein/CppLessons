#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <set>
#include <string>
#include <utility>

struct point_t
{
	point_t()
		:x(0.), y(0.)
	{}
	point_t(double x, double y)
		:x(x), y(y)
	{}
	double x;
	double y;
};

int main()
{
	sf::Image code_hard;
	if (!code_hard.loadFromFile("code.png"))
		return -1;
	int WINDOW_WIDTH = code_hard.getSize().x;
	int WINDOW_HEIGHT = code_hard.getSize().y;

	sf::Color color = code_hard.getPixel(0,0);
	std::vector<point_t> block;
	std::vector<point_t> max_el_block;
	int area = WINDOW_HEIGHT * WINDOW_WIDTH;
	for (int h = 0; h < WINDOW_HEIGHT; ++h)
	{
		for (int w = 0; w < WINDOW_WIDTH; ++w)
		{
			point_t pos = point_t(w, h);
			sf::Color color_pix = code_hard.getPixel(w, h);
			if (color == color_pix)
			{
				block.push_back(pos);
				color_pix = color;
				if (max_el_block.size() != 0)
				{

					if (max_el_block[0].x < pos.x)
					{
						max_el_block.clear();
						max_el_block.push_back(pos);
					}
					else if (max_el_block[0].x == pos.x)
						max_el_block.push_back(pos);
				}
				else
					max_el_block.push_back(pos);
			}
		}
	}
	for (int i = 0; i < max_el_block.size(); ++i)
	{
		std::cout << max_el_block[i].x << " - " << max_el_block[i].y << "\n";
	}
	system("pause");
	return 0;
}