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

void blocks(sf::Image &code_hard, sf::Color &color, blocks_graph_t  &blocks_graph)
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

void final_point(std::vector<point_t> &max_x, std::string &cc, point_t &dc, point_t &find_point)
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

	blocks(code_hard, color, blocks_graph);//вершина и её ребра
	
	std::set<point_t> visited;
	std::vector<point_t> max_x;
	max_x.push_back(pos);
	DFS(pos, blocks_graph, visited, max_x, dc);
	final_point(max_x, cc, dc , find_point);

	std::cout << find_point.x << " - " << find_point.y << "\n";

	system("pause");
	return 0;
}