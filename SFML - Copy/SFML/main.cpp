#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <iterator>
#include <deque>

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

int direct_compare(point_t const &a, point_t const &b, point_t dir)
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

void DFS(point_t current, blocks_graph_t blocks_graph, std::set<point_t> &visited, std::vector<point_t> &max_x, point_t &dp)
{
	visited.insert(current);
	std::cout << "we are in (" << current.x << ", " << current.y << ")" << std::endl;

	if (direct_compare(max_x[0], current, dp) == 0)
		max_x.push_back(current);
	else if (direct_compare(max_x[0], current, dp) == 1)
	{
		max_x.clear();
		max_x.push_back(current);
	}
	
	for (auto iter = blocks_graph[current].begin(); iter != blocks_graph[current].end(); ++iter) // Для каждого ребра
	{
		point_t &next = *iter;
		if (visited.find(next) == visited.end())
				DFS(next, blocks_graph, visited, max_x, dp); // Запускаемся из соседа		
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

int set_color_tab(sf::Color &color)
{
	int color_tab = 0;

	if ((color.r == 255) || (color.g == 255) || (color.b == 255))//формирование оттенка
	{
		if ((color.r == 12) || (color.g == 12) || (color.b == 12))
			color_tab = 10;//самый светлый цвет
		else
			color_tab = 20;//средний
	}
	else
		color_tab = 30;//тёмный

	//далее поиск конкретного цвета
	if (color.g == color.b)
	{
		if ((color_tab == 10) && (color.g == 255))
			color_tab += 3;//голубой
		else
			color_tab += 6;//красный
	}
	else if (color.r == color.g)
	{
		if ((color_tab == 10) && (color.r == 255))
			color_tab += 5;//жёлтый
		else
			color_tab += 2;//синий
	}
	else if (color.r == color.b)
	{
		if ((color_tab == 10) && (color.r == 12))
			color_tab += 4;//зелёный
		else
			color_tab += 1;//фиолетовый
	}
	return color_tab;
};

void final_point(sf::Image &code_hard, std::vector<point_t> &max_x, point_t &dir, point_t &dp, point_t &pos, bool &end_pogram)
{
	sf::Color color = code_hard.getPixel(pos.x, pos.y);
	int cipher_color = set_color_tab(color);

	auto find_point = std::max_element(max_x.begin(), max_x.end(),
		[dir](point_t const &a, point_t const &b)
		{
			return direct_compare(a, b, dir) < 0;
		});
	

	if ((find_point->x + dp.x <= code_hard.getSize().x) && (find_point->y + dp.y <= code_hard.getSize().y))
	{
		point_t next(find_point->x + dp.x, find_point->y + dp.y);
		sf::Color color_next = code_hard.getPixel(next.x, next.y);
		if ((color_next.r == 255) && (color_next.g == 255) && (color_next.b == 255))//если белый, то нужен другой максимум
		{
			std::vector<point_t> next_max;
			for (int i = 0; i < max_x.size(); ++i)
				if ((find_point->x != max_x[i].x) && (find_point->y != max_x[i].y))
					next_max.push_back(max_x[i]);

			max_x.clear();
			max_x = next_max;
			final_point(code_hard, max_x, dir, dp, pos, end_pogram);
		}
		else if ((color_next.r == 0) && (color_next.g == 0) && (color_next.b == 0))//если чёрный, то конец программы
			end_pogram = true;
		else
		{
			int cipher_color_next = set_color_tab(color_next);


			pos = next;
		}
	}
	std::cout << find_point->x << " - " << find_point->y << "\n";
};

void forming_dir(point_t &dp, std::string &cc, point_t &dir)
{
	if (cc == "left")
	{
		if (dp.x == 0)
		{
			dir.x = (-dp.y);
			dir.y = (-dp.x);
		}
		if (dp.x != 0)
		{
			dir.x = dp.y;
			dir.y = dp.x;
		}
	}
	if (cc == "right")
	{
		if (dp.x == 0)
		{
			dir.x = dp.y;
			dir.y = dp.x;
		}
		if (dp.x != 0)
		{
			dir.x = (-dp.y);
			dir.y = (-dp.x);
		}
	}
};

void actions(int &prev_color, int &col_tab, std::deque<int> stack_prog, blocks_graph_t  &blocks_graph, point_t &dp)
{
	int intermediate;
	intermediate = prev_color - col_tab;
	int change_br = abs(intermediate / 10);
	int change_tone = abs(intermediate % 10);

	if (change_tone == 0)
	{
		if (change_br == 1)//push
		{
			stack_prog.push_back(blocks_graph.size());
		}
		else if (change_br == 2)//pop
		{
			stack_prog.pop_back();
		}
	}
	else if (change_tone == 1)
	{
		if (change_br == 0)
		{
			//add
		}
		else if (change_br == 1)
		{
			//substract
		}
		else if (change_br == 2)
		{
			//multiply
		}
	}
	else if (change_tone == 2)
	{
		if (change_br == 0)
		{
			//divide
		}
		else if (change_br == 1)
		{
			//mod
		}
		else if (change_br == 2)//not
		{
			if (stack_prog[0] == 0)
				stack_prog[0] = 1;
			else
				stack_prog[0] = 0;
		}
	}
	else if (change_tone == 3)
	{
		if (change_br == 0)	//greater
		{
			if (stack_prog[stack_prog.size() - 1] > stack_prog[stack_prog.size()])
			{
				stack_prog.pop_back();
				stack_prog.pop_back();
				stack_prog.push_back(1);
			}
			else
			{
				stack_prog.pop_back();
				stack_prog.pop_back();
				stack_prog.push_back(0);
			}
		}
		else if (change_br == 1)
		{
			//pointer
		}
		else if (change_br == 2)
		{
			//switch
		}
	}
	else if (change_tone == 4)
	{
		if (change_br == 0)//duplicate: добавляет в стек копию его верхнего элемента.
		{
			int duplicated = stack_prog[stack_prog.size()];
			stack_prog.push_back(duplicated);
		}
		else if (change_br == 1)
		{
			//roll
		}
		else if (change_br == 2)
		{
			//in(int)
		}
	}
	else if (change_tone == 5)
	{
		if (change_br == 0)
		{
			//in(char)
		}
		else if (change_br == 1)
		{
			//out(int)
		}
		else if (change_br == 2)
		{
			//out(char)
		}
	}	
}

int main()
{
	sf::Image code_hard;
	if (!code_hard.loadFromFile("code.png"))
		return -1;

	bool end_pogram = false;
	point_t pos(0, 0);//первая точка
	point_t dp(1, 0);
	point_t find_point(0, 0);
	std::string cc = "right";
	blocks_graph_t blocks_graph;
	point_t dir(0, 0);
	forming_dir(dp, cc, dir);
	blocks(code_hard, blocks_graph);//вершина и её ребра
	
	std::deque<int> stack_prog;
	std::set<point_t> visited;
	std::vector<point_t> max_x;
	max_x.push_back(pos);
	DFS(pos, blocks_graph, visited, max_x, dp);
	final_point(code_hard, max_x, dir, dp, pos, end_pogram);
	while (end_pogram == false)
	{
		int size_prev = max_x.size();
		max_x.clear();
		visited.clear();
		max_x.push_back(pos);
		DFS(pos, blocks_graph, visited, max_x, dp);
		final_point(code_hard, max_x, dir, dp, pos, end_pogram);
	}
	std::cout << find_point.x << " - " << find_point.y << "\n";

	system("pause");
	return 0;
}