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
typedef std::map<point_t, std::vector<point_t>> blocks_graph_t;

void DFS(point_t current, blocks_graph_t &blocks_graph, std::set<point_t> &visited, std::vector<point_t> &max_x)
{
	visited.insert(current);
	std::cout << "we are in (" << current.x << ", " << current.y << ")" << std::endl;

	if (max_x[0].x < current.x)
	{
		max_x.clear();
		max_x.push_back(current);
	}
	else if (max_x[0].x == current.x)
		max_x.push_back(current);

	for (auto iter = blocks_graph[current].begin(); iter != blocks_graph[current].end(); ++iter) // Для каждого ребра
	{
		point_t &next = *iter;
		if (visited.find(next) == visited.end())
				DFS(next, blocks_graph, visited, max_x); // Запускаемся из соседа		
	}
};

int main()
{
	sf::Image code_hard;
	if (!code_hard.loadFromFile("code.png"))
		return -1;
	int width_img = code_hard.getSize().x;
	int height_img = code_hard.getSize().y;

	point_t pos(0,0);//первая точка
	sf::Color color = code_hard.getPixel(0,0);
	blocks_graph_t blocks_graph;//вершина и её ребра

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
	std::set<point_t> visited;
	std::vector<point_t> max_x;
	max_x.push_back(pos);
	DFS(pos, blocks_graph, visited, max_x);
	std::cout << max_x.size() << "\n";
	for (int i = 0; i < max_x.size(); ++i)
		std::cout << max_x[i].x << " - " << max_x[i].y << "\n";
	system("pause");
	return 0;
}