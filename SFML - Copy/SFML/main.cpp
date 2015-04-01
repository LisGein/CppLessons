#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <iterator>
#include <deque>
#include <cctype>

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
				if (code_hard.getPixel(row, col) != sf::Color(255, 255, 255))
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
		}
		else
		{
			for (int row = 0; row < width_img - 1; ++row)
				if (code_hard.getPixel(row, col) != sf::Color(255, 255, 255))
				{
					if (code_hard.getPixel(row, col) == code_hard.getPixel(row + 1, col))
					{
						blocks_graph[point_t(row + 1, col)].push_back(point_t(row, col));
						blocks_graph[point_t(row, col)].push_back(point_t(row + 1, col));
					}
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
			pos = next;
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

void actions(int &prev_color, int &col_tab, std::deque<int> stack_prog,  std::set<point_t> &visited, point_t &dp, std::string &cc)
{
	int intermediate;
	intermediate = prev_color - col_tab;
	int change_br = abs(intermediate / 10);
	int change_tone = abs(intermediate % 10);

	if (change_tone == 0)
	{
		if (change_br == 1)//push
		{
			if (visited.size() != 0)
				stack_prog.push_back(visited.size());
		}
		else if (change_br == 2)//pop
		{
			if (stack_prog.size() != 0)
				stack_prog.pop_back();
		}
	}
	else if (change_tone == 1)
	{
		if (change_br == 0)//add
		{
			
		}
		else if (change_br == 1)//subtract - извлекает из стека два верхних элемента, выполняет соответствующую операцию и добавляет результат в стек.
								//Первым операндом является элемент, который был глубже в стеке
		{
			if (stack_prog.size() > 1)
			{
				int mod_stack = (stack_prog[stack_prog.size() - 2] - stack_prog[stack_prog.size() - 1]);
				stack_prog.pop_back();
				stack_prog.pop_back();
				stack_prog.push_back(mod_stack);
			}
		}
		else if (change_br == 2)//multiply - извлекает из стека два верхних элемента, выполняет соответствующую операцию и добавляет результат в стек.
								//Первым операндом является элемент, который был глубже в стеке
		{
			if (stack_prog.size() > 1)
			{
				int mod_stack = (stack_prog[stack_prog.size() - 2] * stack_prog[stack_prog.size() - 1]);
				stack_prog.pop_back();
				stack_prog.pop_back();
				stack_prog.push_back(mod_stack);
			}			
		}
	}
	else if (change_tone == 2)
	{
		if (change_br == 0) //divide - извлекает из стека два верхних элемента, выполняет соответствующую операцию и добавляет результат в стек.
							//Первым операндом является элемент, который был глубже в стеке
		{
			if (stack_prog.size() > 1)
			{
				int mod_stack = (stack_prog[stack_prog.size() - 2] / stack_prog[stack_prog.size() - 1]);
				stack_prog.pop_back();
				stack_prog.pop_back();
				stack_prog.push_back(mod_stack);
			}
		}
		else if (change_br == 1)//mod - извлекает из стека два верхних элемента, выполняет соответствующую операцию и добавляет результат в стек.
								//Первым операндом является элемент, который был глубже в стеке
		{
			if (stack_prog.size() > 1)
			{
				int mod_stack = (stack_prog[stack_prog.size() - 2] % stack_prog[stack_prog.size() - 1]);
				stack_prog.pop_back();
				stack_prog.pop_back();
				stack_prog.push_back(mod_stack);
			}
		}
		else if (change_br == 2)//not - заменяет верхний элемент стека на 0, если он был не нулевым, и на 1 в противном случае.
		{
			if (stack_prog.size() != 0)
			{
				if (stack_prog[stack_prog.size() - 1] == 0)
					stack_prog[stack_prog.size() - 1] = 1;
				else
					stack_prog[stack_prog.size() - 1] = 0;
			}
		}
	}
	else if (change_tone == 3)
	{
		if (change_br == 0)	//greater - извлекает из стека два верхних элемента и добавляет в него 1, если более глубокое значение больше,
							//и 0 в противном случае.
		{
			if (stack_prog.size() > 1)
			{
				if (stack_prog[stack_prog.size() - 2] > stack_prog[stack_prog.size()] - 1)
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
		}
		else if (change_br == 1)//pointer - извлекает из стека элемент и поворачивает DP на (90*значение) градусов по часовой стрелке
								//(для отрицательных значений - против часовой).
		{
			if (stack_prog.size() != 0)
			{
				point_t dir;
				std::string direction;
				if ((stack_prog[stack_prog.size()] - 1) < 0)
					direction = "left";
				else
					direction = "right";
				forming_dir(dp, direction, dir);
				dp = dir;
			}
		}
		else if (change_br == 2)//switch - извлекает из стека элемент и меняет направление CC на противоположное, если элемент нечетный.
		{
			if (stack_prog.size() != 0)
			{
				int modulo = (stack_prog[stack_prog.size() - 1] % 2);
				if (modulo != 0)
				{
					if (cc == "left")
						cc = "right";
					else
						cc = "left";
				}
				stack_prog.pop_back();
			}
		}
	}
	else if (change_tone == 4)
	{
		if (change_br == 0)//duplicate: добавляет в стек копию его верхнего элемента.
		{
			if (stack_prog.size() != 0)
			{
				int duplicated = stack_prog[stack_prog.size() - 1];
				stack_prog.push_back(duplicated);
			}
		}
		else if (change_br == 1)
			/*roll извлекает из стека верхнее значение M и следующее за ним N и выполняет M операций roll на глубину N каждая.
			Одна операция roll на глубину N определяется как перемещение верхнего элемента стека на N элементов в глубину стека и перемещение
			всех элементов выше N на 1 вверх. Глубина N не может быть отрицательной, тогда как количество операций M может быть (тогда roll 
			выполняется в обратном направлении).*/
		{
			
		}
		else if (change_br == 2)//in(int)
		{
			int input_num;
			std::cin >> input_num;
			stack_prog.push_back(input_num);
		}
	}
	else if (change_tone == 5)
	{
		if (change_br == 0)
		{
			char word;
			std::cin >> word;
			if (std::isalpha((unsigned char)word))
			{
				int alp_in_numb = (char)tolower(word) - 'a';
				stack_prog.push_back(alp_in_numb);
			}			
		}
		else if (change_br == 1)//out(int) - извлекает элемент из стека и выводит его на печать как число или символ в зависимости от типа команды.
		{
			if (stack_prog.size() != 0)
			{
				std::cout << stack_prog[stack_prog.size() - 1] << std::endl;
				stack_prog.pop_back();
			}
		}
		else if (change_br == 2)//out(char) - извлекает элемент из стека и выводит его на печать как число или символ в зависимости от типа команды.
		{
			if (stack_prog.size() != 0)
			{
				char alp_in_numb = stack_prog[stack_prog.size() - 1] + 'a';
				std::cout << alp_in_numb << std::endl;
				stack_prog.pop_back();
			}
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
	std::deque<int> stack_prog;
	blocks(code_hard, blocks_graph);//вершина и её ребра
	
	std::set<point_t> visited;
	std::vector<point_t> max_x;
	max_x.push_back(pos);

	sf::Color color = code_hard.getPixel(pos.x, pos.y);
	DFS(pos, blocks_graph, visited, max_x, dp);
	forming_dir(dp, cc, dir);
	final_point(code_hard, max_x, dir, dp, pos, end_pogram);
	if (color != sf::Color(255, 255, 255))
	{
		int cipher_color = set_color_tab(color);
		sf::Color color_next = code_hard.getPixel(pos.x, pos.y);
		int cipher_color_next = set_color_tab(color_next);
		actions(cipher_color, cipher_color_next, stack_prog, visited, dp, cc);
	}
	visited.clear();
	max_x.clear();
	while (end_pogram == false)
	{
		max_x.push_back(pos);

		color = code_hard.getPixel(pos.x, pos.y);
		DFS(pos, blocks_graph, visited, max_x, dp);
		forming_dir(dp, cc, dir);
		final_point(code_hard, max_x, dir, dp, pos, end_pogram);
		if (color != sf::Color(255, 255, 255))
		{
			int cipher_color = set_color_tab(color);
			sf::Color color_next = code_hard.getPixel(pos.x, pos.y);
			int cipher_color_next = set_color_tab(color_next);
			actions(cipher_color, cipher_color_next, stack_prog, visited, dp, cc);
		}
		visited.clear();
		max_x.clear();
	}
	system("pause");
	return 0;
}