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
	bool operator< (point_t &other)
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

void DFS(point_t current, blocks_graph_t &blocks_graph)
{
	std::set<point_t> visited;
	visited.insert(current);
	std::cout << "we are in (" << current.x << ", " << current.y << ")" << std::endl;
	std::vector<point_t> max_x;
	for (point_t const & next : blocks_graph[current]) // Для каждого ребра
	{
		if (visited.find(next) == visited.end())
		{
			max_x.push_back(next);
			DFS(next, blocks_graph); // Запускаемся из соседа
		}
	}
	for (int i = 0; i < max_x.size(); ++i)
	std::cout << max_x[i].x << " - " << max_x[i].y << "\n";
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
	for (int row = 0; row < WINDOW_WIDTH; ++row)
	{
		for (int col = 0; col < WINDOW_HEIGHT - 1; ++col) //-1!!!!&!?!?!?!
		{
			if (code_hard.getPixel(row, col) == code_hard.getPixel(row, col + 1))//если ячейки (row, col) и (row, col + 1) одного цвета
			{
				blocks_graph[point_t(row, col)].push_back(point_t(row, col));
				blocks_graph[point_t(row, col + 1)].push_back(point_t(row, col + 1));
			}
		}
	}
	DFS(pos, blocks_graph);

	system("pause");
	return 0;
}