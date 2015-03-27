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
	for (auto iter = blocks_graph[current].begin(); iter != blocks_graph[current].end(); ++iter) // Для каждого ребра
	{
		point_t &next = *iter;
		if (visited.find(next) == visited.end())
		{
			if (max_x[0].x < next.x)
			{
				max_x.clear();
				max_x.push_back(next);
			}
			else if (max_x[0].x == next.x)
			{
				bool find_max = false;
				for (int i_y = 0; i_y < max_x.size(); ++i_y)
				{
					if (max_x[i_y].y < next.y)
						find_max = true;
					if (max_x[i_y].y > next.y)
						find_max = false;
				}
				if (find_max == true)
					max_x.push_back(next);
				find_max = false;
			}
			DFS(next, blocks_graph, visited, max_x); // Запускаемся из соседа
		}
	}
};

int main()
{
	sf::Image code_hard;
	if (!code_hard.loadFromFile("code.png"))
		return -1;
	int WINDOW_WIDTH = code_hard.getSize().x;
	int WINDOW_HEIGHT = code_hard.getSize().y;

	point_t pos(0,0);//первая точка
	sf::Color color = code_hard.getPixel(0,0);
	blocks_graph_t blocks_graph;//вершина и её ребра
	for (int col = 0; col < WINDOW_HEIGHT; ++col) 
	{
		if (col != WINDOW_HEIGHT - 1)
		{
			for (int row = 0; row < WINDOW_WIDTH; ++row)
			{
				if (row != WINDOW_WIDTH - 1)//если x != ширине
				{
					if (code_hard.getPixel(row, col) == code_hard.getPixel(row + 1, col))//если ячейки (row, col) и (row + 1, col) одного цвета
					{
						blocks_graph[point_t(row, col)].push_back(point_t(row, col));
						blocks_graph[point_t(row, col)].push_back(point_t(row + 1, col));
						if (code_hard.getPixel(row, col) == code_hard.getPixel(row, col + 1))
							blocks_graph[point_t(row, col)].push_back(point_t(row, col + 1));

					}
					else if (code_hard.getPixel(row, col) == code_hard.getPixel(row, col + 1))
					{
						blocks_graph[point_t(row, col)].push_back(point_t(row, col));
						blocks_graph[point_t(row, col)].push_back(point_t(row, col + 1));
					}
				}
				else if (code_hard.getPixel(row, col) == code_hard.getPixel(row, col + 1))
				{
					blocks_graph[point_t(row, col)].push_back(point_t(row, col));
					blocks_graph[point_t(row, col)].push_back(point_t(row, col + 1));
				}
			}
		}
		else
		{
			for (int row = 0; row < WINDOW_WIDTH; ++row)  
				if (row != WINDOW_WIDTH - 1)
					if (code_hard.getPixel(row, col) == code_hard.getPixel(row + 1, col))
					{
						blocks_graph[point_t(row, col)].push_back(point_t(row, col));
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