#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <set>
#include <string>
#include <utility>

struct point_t
{
	point_t()
		:x(0), y(0)
	{}
	point_t(int x, int y)
		:x(x), y(y)
	{}
	bool operator< (point_t const &other) const
	{
		if (y < other.y)
			return true;
		if (y == other.y && x < other.x)
			return true;
		return false;
	}
	int x;
	int y;
};

std::vector<point_t> final_max(point_t &dc, point_t &current, std::vector<point_t> &max_x)
{
	if (dc.y == 0)
	{
		if (max_x[0].x == current.x)
			max_x.push_back(current);
		else if (dc.x == 1)
			if (max_x[0].x < current.x)
			{
				max_x.clear();
				max_x.push_back(current);
			}
		else if (dc.x == -1)
			if (max_x[0].x > current.x)
			{
				max_x.clear();
				max_x.push_back(current);
			}
	}
	else if (dc.x == 0)
	{
		if (max_x[0].y == current.y)
			max_x.push_back(current);
		else if (dc.y == 1)
			if (max_x[0].y < current.y)
			{
				max_x.clear();
				max_x.push_back(current);
			}
		else if (dc.y == -1)		
			if (max_x[0].y > current.y)
			{
				max_x.clear();
				max_x.push_back(current);
			}		
	}
	return max_x;
};

typedef std::map<point_t, std::vector<point_t>> blocks_graph_t;

void DFS(point_t current, blocks_graph_t &blocks_graph, std::set<point_t> &visited, std::vector<point_t> &max_x, point_t &dc)
{
	visited.insert(current);
	std::cout << "we are in (" << current.x << ", " << current.y << ")" << std::endl;
	max_x = final_max(dc, current, max_x);

	for (auto iter = blocks_graph[current].begin(); iter != blocks_graph[current].end(); ++iter) // Для каждого ребра
	{
		point_t &next = *iter;
		if (visited.find(next) == visited.end())
				DFS(next, blocks_graph, visited, max_x, dc); // Запускаемся из соседа		
	}
};

void blocks(sf::Image &code_hard, blocks_graph_t  &blocks_graph, point_t &pos, point_t &dc, std::string &cc)
{
	int width_img = code_hard.getSize().x;
	int height_img = code_hard.getSize().y;
	if (((dc.x == 1) && (cc == "right")) || ((dc.y == 1) && (cc == "left")) || ((dc.x == -1) && (cc == "left")) || ((dc.y == 1) && (cc == "right")))
	{
		for (int col = pos.y; col < height_img; ++col)
		{
			if (col != height_img - 1)
			{
				if (((dc.x == 1) && (cc == "right")) || ((dc.y == 1) && (cc == "left")))
				{
					for (int row = pos.x; row < width_img - 1; ++row)
					{

						if (code_hard.getPixel(row, col) == code_hard.getPixel(row + 1, col))//если ячейки (row, col) и (row + 1, col) одного цвета
						{
							blocks_graph[point_t(row + 1, col)].push_back(point_t(row, col));
							blocks_graph[point_t(row, col)].push_back(point_t(row + 1, col));
							if (code_hard.getPixel(row, col) == code_hard.getPixel(row, col + 1))
								blocks_graph[point_t(row, col)].push_back(point_t(row, col + 1));

						}
						else if (code_hard.getPixel(row, col) == code_hard.getPixel(row, col + 1))
						{
							blocks_graph[point_t(row, col + 1)].push_back(point_t(row, col));
							blocks_graph[point_t(row, col)].push_back(point_t(row, col + 1));
						}
					}
				}
				else if (((dc.x == -1) && (cc == "left")) || ((dc.y == 1) && (cc == "right")))
				{
					for (int row = pos.x; row > 1; --row)
					{

						if (code_hard.getPixel(row, col) == code_hard.getPixel(row--, col))//если ячейки (row, col) и (row + 1, col) одного цвета
						{
							blocks_graph[point_t(row--, col)].push_back(point_t(row, col));
							blocks_graph[point_t(row, col)].push_back(point_t(row--, col));
							if (code_hard.getPixel(row, col) == code_hard.getPixel(row, col + 1))
								blocks_graph[point_t(row, col)].push_back(point_t(row, col + 1));

						}
						else if (code_hard.getPixel(row, col) == code_hard.getPixel(row, col + 1))
						{
							blocks_graph[point_t(row, col + 1)].push_back(point_t(row, col));
							blocks_graph[point_t(row, col)].push_back(point_t(row, col + 1));
						}
					}
				}
			}
			else
			{
				if (((dc.x == 1) && (cc == "right")) || ((dc.y == 1) && (cc == "left")))
				{
					for (int row = pos.x; row < width_img - 1; ++row)
						if (code_hard.getPixel(row, col) == code_hard.getPixel(row + 1, col))
						{
							blocks_graph[point_t(row + 1, col)].push_back(point_t(row, col));
							blocks_graph[point_t(row, col)].push_back(point_t(row + 1, col));
						}
				}
				else if (((dc.x == -1) && (cc == "left")) || ((dc.y == 1) && (cc == "right")))
				{
					for (int row = pos.x; row > 1; --row)
						if (code_hard.getPixel(row, col) == code_hard.getPixel(row--, col))
						{
							blocks_graph[point_t(row--, col)].push_back(point_t(row, col));
							blocks_graph[point_t(row, col)].push_back(point_t(row--, col));
						}
				}
			}
		}
	}

	if (((dc.x == 1) && (cc == "left")) || ((dc.y == -1) && (cc == "right")) || ((dc.x == -1) && (cc == "right")) || ((dc.y == -1) && (cc == "left")))
	{
		for (int col = pos.y; col < height_img; ++col)
		{
			if (col != height_img - 1)
			{
				if (((dc.x == 1) && (cc == "left")) || ((dc.y == -1) && (cc == "right")))
				{
					for (int row = pos.x; row < width_img - 1; ++row)
					{

						if (code_hard.getPixel(row, col) == code_hard.getPixel(row + 1, col))//если ячейки (row, col) и (row + 1, col) одного цвета
						{
							blocks_graph[point_t(row + 1, col)].push_back(point_t(row, col));
							blocks_graph[point_t(row, col)].push_back(point_t(row + 1, col));
							if (code_hard.getPixel(row, col) == code_hard.getPixel(row, col + 1))
								blocks_graph[point_t(row, col)].push_back(point_t(row, col + 1));

						}
						else if (code_hard.getPixel(row, col) == code_hard.getPixel(row, col + 1))
						{
							blocks_graph[point_t(row, col + 1)].push_back(point_t(row, col));
							blocks_graph[point_t(row, col)].push_back(point_t(row, col + 1));
						}
					}
				}
				else if (((dc.x == -1) && (cc == "right")) || ((dc.y == -1) && (cc == "left")))
				{
					for (int row = pos.x; row > 1; --row)
					{

						if (code_hard.getPixel(row, col) == code_hard.getPixel(row--, col))//если ячейки (row, col) и (row + 1, col) одного цвета
						{
							blocks_graph[point_t(row--, col)].push_back(point_t(row, col));
							blocks_graph[point_t(row, col)].push_back(point_t(row--, col));
							if (code_hard.getPixel(row, col) == code_hard.getPixel(row, col + 1))
								blocks_graph[point_t(row, col)].push_back(point_t(row, col + 1));

						}
						else if (code_hard.getPixel(row, col) == code_hard.getPixel(row, col + 1))
						{
							blocks_graph[point_t(row, col + 1)].push_back(point_t(row, col));
							blocks_graph[point_t(row, col)].push_back(point_t(row, col + 1));
						}
					}
				}
			}
			else
			{
				if (((dc.x == 1) && (cc == "left")) || ((dc.y == -1) && (cc == "right")))
				{
					for (int row = pos.x; row < width_img - 1; ++row)
						if (code_hard.getPixel(row, col) == code_hard.getPixel(row + 1, col))
						{
							blocks_graph[point_t(row + 1, col)].push_back(point_t(row, col));
							blocks_graph[point_t(row, col)].push_back(point_t(row + 1, col));
						}
				}
				else if (((dc.x == -1) && (cc == "right")) || ((dc.y == -1) && (cc == "left")))
				{
					for (int row = pos.x; row > 1; --row)
						if (code_hard.getPixel(row, col) == code_hard.getPixel(row--, col))
						{
							blocks_graph[point_t(row--, col)].push_back(point_t(row, col));
							blocks_graph[point_t(row, col)].push_back(point_t(row--, col));
						}
				}
			}
		}
	}
};

void final_point(sf::Image &code_hard, std::vector<point_t> &max_x, std::string &cc, point_t &dc, point_t &find_point, point_t &pos)
{
	if (((dc.x == 1)&&(cc == "right"))||((dc.x == -1)&&(cc == "left")))
	{
		for (int i = 0; i < max_x.size(); ++i)
		{
			if (find_point.y < max_x[i].y)
				find_point = max_x[i];
		}
	}
	else if (((dc.x == 1)&&(cc == "left"))||((dc.x == -1)&&(cc == "right")))
	{
		for (int i = 0; i < max_x.size(); ++i)
		{
			if (find_point.y > max_x[i].y)
				find_point = max_x[i];
		}
	}
	else if (((dc.y == -1)&&(cc == "right"))||((dc.y == 1)&&(cc == "left")))
	{
		for (int i = 0; i < max_x.size(); ++i)
		{
			if (find_point.x < max_x[i].x)
				find_point = max_x[i];
		}
	}
	else if (((dc.y == -1) && (cc == "left")) || ((dc.y == 1) && (cc == "right")))
	{
		for (int i = 0; i < max_x.size(); ++i)
		{
			if (find_point.x > max_x[i].x)
				find_point = max_x[i];
		}
	}
	int width_img = code_hard.getSize().x;
	int height_img = code_hard.getSize().y;
	if ((find_point.x + dc.x <= width_img) && (find_point.y + dc.y <= height_img))
	{
		point_t next(find_point.x + dc.x, find_point.y + dc.y);
		sf::Color color_next = code_hard.getPixel(next.x, next.y);
		if ((color_next.r == 255) && (color_next.g == 255) && (color_next.b == 255))//если белый, то нужен другой максимум
		{
			std::vector<point_t> next_max;
			for (int i = 0; i < max_x.size(); ++i)
				if ((find_point.x != max_x[i].x) && (find_point.y != max_x[i].y))
					next_max.push_back(max_x[i]);

			max_x.clear();
			max_x = next_max;
			final_point(code_hard, max_x, cc, dc, find_point, pos);
		}
		//else if ((color_next.r == 0) && (color_next.g == 0) && (color_next.b == 0))//если чёрный, то конец программы
		else
			pos = next;
	}
	
};

int main()
{
	sf::Image code_hard;
	if (!code_hard.loadFromFile("code.png"))
		return -1;

	point_t pos(0, 0);//первая точка
	point_t dc(1, 0);
	point_t find_point(0, 0);
	std::string cc = "right";
	sf::Color color = code_hard.getPixel(0,0);
	blocks_graph_t blocks_graph;

	blocks(code_hard, blocks_graph, pos, dc, cc);//вершина и её ребра
	
	std::set<point_t> visited;
	std::vector<point_t> max_x;
	max_x.push_back(pos);
	DFS(pos, blocks_graph, visited, max_x, dc);
	final_point(code_hard, max_x, cc, dc, find_point, pos);
	while (true)
	{
		int size_prev = max_x.size();
		sf::Color color_prev = color;
		max_x.clear();
		visited.clear();
		 color = code_hard.getPixel(pos.x, pos.y);
		blocks(code_hard, blocks_graph, pos, dc, cc);
		max_x.push_back(pos);
		DFS(pos, blocks_graph, visited, max_x, dc);
		final_point(code_hard, max_x, cc, dc, find_point, pos);
	}
	std::cout << find_point.x << " - " << find_point.y << "\n";

	system("pause");
	return 0;
}