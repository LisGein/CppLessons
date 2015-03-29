#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <iterator>

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

int direct_compare(point_t &a, point_t &b, point_t &dir)
{
	if (dir.y == 0)
	{
		if (a.x == b.x)
			return 0;
		else if (dir.x == 1)
		{
			if (a.x < b.x)
				return 1;
		}
		else if (dir.x == -1)
		{
			if (a.x > b.x)
				return 1;
		}
	}
	else if (dir.x == 0)
	{
		if (a.y == b.y)
			return 0;
		else if (dir.y == 1)
		{
			if (a.y < b.y)
				return 1;
		}
		else if (dir.y == -1)
		{
			if (a.y > b.y)
				return 1;
		}
	}
	return -1;
};

typedef std::map<point_t, std::vector<point_t>> blocks_graph_t;

void DFS(point_t current, blocks_graph_t blocks_graph, std::set<point_t> &visited, std::vector<point_t> &max_x, point_t &dc)
{
	visited.insert(current);
	std::cout << "we are in (" << current.x << ", " << current.y << ")" << std::endl;

	if (direct_compare(max_x[0], current, dc) == 0)
		max_x.push_back(current);
	else if (direct_compare(max_x[0], current, dc) == 1)
	{
		max_x.clear();
		max_x.push_back(current);
	}
	
	for (auto iter = blocks_graph[current].begin(); iter != blocks_graph[current].end(); ++iter) // Для каждого ребра
	{
		point_t &next = *iter;
		if (visited.find(next) == visited.end())
				DFS(next, blocks_graph, visited, max_x, dc); // Запускаемся из соседа		
	}
};

void blocks(sf::Image code_hard, blocks_graph_t  &blocks_graph)//построение графоф
{
	int width_img = code_hard.getSize().x;
	int height_img = code_hard.getSize().y;
	for (int col = 0; col < height_img; ++col)
	{
		if (col != height_img - 1)
		{
			for (int row = 0; row < width_img - 1; ++row)
			{
				if (code_hard.getPixel(row, col) == code_hard.getPixel(row + 1, col))//если ячейки (row, col) и (row + 1, col) одного цвета
				{
					blocks_graph[point_t(row + 1, col)].push_back(point_t(row, col));
					blocks_graph[point_t(row, col)].push_back(point_t(row + 1, col));
				}
				if (code_hard.getPixel(row, col) == code_hard.getPixel(row, col + 1))
				{
					blocks_graph[point_t(row, col + 1)].push_back(point_t(row, col));
					blocks_graph[point_t(row, col)].push_back(point_t(row, col + 1));
				}
			}
		}
		else
		{
			for (int row = 0; row < width_img - 1; ++row)
				if (code_hard.getPixel(row, col) == code_hard.getPixel(row + 1, col))
				{
					blocks_graph[point_t(row + 1, col)].push_back(point_t(row, col));
					blocks_graph[point_t(row, col)].push_back(point_t(row + 1, col));
				}
		}
	}
};

void final_point(sf::Image &code_hard, std::vector<point_t> &max_x, point_t &dir, point_t &dc, point_t &pos)
{
	auto find_point = std::max_element(max_x.begin(), max_x.end(),
		[&dir](point_t &a, point_t &b)
		{
			direct_compare(a, b, dir) < 0;
		});
	
	int width_img = code_hard.getSize().x;
	int height_img = code_hard.getSize().y;
	if ((find_point->x + dc.x <= width_img) && (find_point->y + dc.y <= height_img))
	{
		point_t next(find_point->x + dc.x, find_point->y + dc.y);
		sf::Color color_next = code_hard.getPixel(next.x, next.y);
		if ((color_next.r == 255) && (color_next.g == 255) && (color_next.b == 255))//если белый, то нужен другой максимум
		{
			std::vector<point_t> next_max;
			for (int i = 0; i < max_x.size(); ++i)
				if ((find_point->x != max_x[i].x) && (find_point->y != max_x[i].y))
					next_max.push_back(max_x[i]);

			max_x.clear();
			max_x = next_max;
			final_point(code_hard, max_x, dir, dc, pos);
		}
		//else if ((color_next.r == 0) && (color_next.g == 0) && (color_next.b == 0))//если чёрный, то конец программы
		else
			pos = next;
	}
	
};

void forming_dir(point_t &dc, std::string &cc, point_t &dir)
{
	if (cc == "left")
	{
		if (dc.x == 0)
		{
			dir.x = (-dc.y);
			dir.y = (-dc.x);
		}
		if (dc.x != 0)
		{
			dir.x = dc.y;
			dir.y = dc.x;
		}
	}
	if (cc == "right")
	{
		if (dc.x == 0)
		{
			dir.x = dc.y;
			dir.y = dc.x;
		}
		if (dc.x != 0)
		{
			dir.x = (-dc.y);
			dir.y = (-dc.x);
		}
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
	point_t dir(0, 0);
	forming_dir(dc, cc, dir);
	blocks(code_hard, blocks_graph);//вершина и её ребра
	
	std::set<point_t> visited;
	std::vector<point_t> max_x;
	max_x.push_back(pos);
	DFS(pos, blocks_graph, visited, max_x, dc);
	final_point(code_hard, max_x, dir, dc, pos);
	//while (true)
	//{
	std::cout << find_point.x << " - " << find_point.y << "\n";
		int size_prev = max_x.size();
		sf::Color color_prev = color;
		max_x.clear();
		visited.clear();
		color = code_hard.getPixel(pos.x, pos.y);
		max_x.push_back(pos);
		DFS(pos, blocks_graph, visited, max_x, dc);
		final_point(code_hard, max_x, dir, dc, pos);
//	}
	std::cout << find_point.x << " - " << find_point.y << "\n";

	system("pause");
	return 0;
}