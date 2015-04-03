#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <functional>
#include <set>
#include <string>
#include <utility>
#include <iterator>
#include <deque>
#include <cctype>

typedef std::function<void()> action_func_t;

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

int direct_compare(point_t const &a, point_t const &b, point_t dir_)
{
	if (dir_.y == 0)
	{
		if (a.x == b.x)
			return 0;
		else if (dir_.x == 1)
		{
			if (a.x < b.x)
				return 1;
		}
		else if (dir_.x == -1)
		{
			if (a.x > b.x)
				return 1;
		}
	}
	else if (dir_.x == 0)
	{
		if (a.y == b.y)
			return 0;
		else if (dir_.y == 1)
		{
			if (a.y < b.y)
				return 1;
		}
		else if (dir_.y == -1)
		{
			if (a.y > b.y)
				return 1;
		}
	}
	return -1;
}

class Interpretator
{	
public:
	struct hue_lightness_t
	{
		hue_lightness_t()
			:hue(0)
			, lightnes(0)
		{}
		hue_lightness_t(size_t hue, size_t lightnes)
			:hue(hue)
			, lightnes(lightnes)
		{}
		//constructor
		size_t hue;
		size_t lightnes;
		//operator <
		bool operator< (hue_lightness_t const &other) const
		{
			if (lightnes < other.lightnes)
				return true;
			if (lightnes == other.lightnes && hue < other.hue)
				return true;
			return false;
		}
	};

	Interpretator(sf::Image const &code_hard)
		:code_hard_(code_hard)
		, dp_(1, 0)
		, cc_("right")
		, pos_(0, 0)
		, dir_(0, 0)
		, end_program(false)
		, step_att(0)
	{	
		blocks();
		actions_map_[hue_lightness_t(0, 0)] = std::bind(&Interpretator::empty_ac, this);
		actions_map_[hue_lightness_t(1, 0)] = std::bind(&Interpretator::push, this);
		actions_map_[hue_lightness_t(2, 0)] = std::bind(&Interpretator::pop, this);

		actions_map_[hue_lightness_t(0, 1)] = std::bind(&Interpretator::add, this); //первый способ
		actions_map_[hue_lightness_t(1, 1)] = [this](){ substract(); }; //второй способ
		actions_map_[hue_lightness_t(2, 1)] = std::bind(&Interpretator::multiply, this);

		actions_map_[hue_lightness_t(0, 2)] = std::bind(&Interpretator::divide, this);
		actions_map_[hue_lightness_t(1, 2)] = std::bind(&Interpretator::mod, this);
		actions_map_[hue_lightness_t(2, 2)] = std::bind(&Interpretator::not, this);

		actions_map_[hue_lightness_t(0, 3)] = std::bind(&Interpretator::greater, this);
		actions_map_[hue_lightness_t(1, 3)] = std::bind(&Interpretator::pointer, this);
		actions_map_[hue_lightness_t(2, 3)] = std::bind(&Interpretator::switch_array, this);

		actions_map_[hue_lightness_t(0, 4)] = std::bind(&Interpretator::duplicate, this);
		actions_map_[hue_lightness_t(1, 4)] = std::bind(&Interpretator::roll, this);
		actions_map_[hue_lightness_t(2, 4)] = std::bind(&Interpretator::in_int, this);

		actions_map_[hue_lightness_t(0, 5)] = std::bind(&Interpretator::in_char, this);
		actions_map_[hue_lightness_t(1, 5)] = std::bind(&Interpretator::out_int, this);
		actions_map_[hue_lightness_t(2, 5)] = std::bind(&Interpretator::out_char, this);
	};

	bool finished()
	{
		return end_program;
	}
	void step()
	{ 
		max_x_.push_back(pos_);
		sf::Color color = code_hard_.getPixel(pos_.x, pos_.y);
		DFS(pos_);
		forming_dir(cc_);
		final_point(step_att);
		sf::Color color_next = code_hard_.getPixel(pos_.x, pos_.y);
		if ((color != sf::Color(255, 255, 255)) && (color_next != sf::Color(0, 0, 0)))
		{		
			int cipher_color = set_color_tab(color);
			int cipher_color_next = set_color_tab(color_next);
			int intermediate = cipher_color - cipher_color_next;
			hue_lightness_t color_change;
			color_change.hue = abs(intermediate / 10);
			color_change.lightnes = abs(intermediate % 10);
			action(color_change);
		}
		visited_.clear();
		max_x_.clear();
	};
private:
	void blocks()//построение графоф
	{
		int width_img = code_hard_.getSize().x;
		int height_img = code_hard_.getSize().y;

		for (int col = 0; col < height_img; ++col)
		{
			if (col != height_img - 1)
			{
				for (int row = 0; row < width_img - 1; ++row)
				{
					if (code_hard_.getPixel(row, col) != sf::Color(255, 255, 255))
					{
						if (code_hard_.getPixel(row, col) == code_hard_.getPixel(row + 1, col))//если ячейки (row, col) и (row + 1, col) одного цвета
						{
							blocks_graph_[point_t(row + 1, col)].push_back(point_t(row, col));
							blocks_graph_[point_t(row, col)].push_back(point_t(row + 1, col));
						}
						if (code_hard_.getPixel(row, col) == code_hard_.getPixel(row, col + 1))
						{
							blocks_graph_[point_t(row, col + 1)].push_back(point_t(row, col));
							blocks_graph_[point_t(row, col)].push_back(point_t(row, col + 1));
						}
					}
				}
			}
			else
			{
				for (int row = 0; row < width_img - 1; ++row)
					if (code_hard_.getPixel(row, col) != sf::Color(255, 255, 255))
					{
						if (code_hard_.getPixel(row, col) == code_hard_.getPixel(row + 1, col))
						{
							blocks_graph_[point_t(row + 1, col)].push_back(point_t(row, col));
							blocks_graph_[point_t(row, col)].push_back(point_t(row + 1, col));
						}
					}
			}
		}
	};
	void DFS(point_t current)
	{
		visited_.insert(current);
		std::cout << "we are in (" << current.x << ", " << current.y << ")" << std::endl;

		if (direct_compare(max_x_[0], current, dir_) == 0)
			max_x_.push_back(current);
		else if (direct_compare(max_x_[0], current, dir_) == -1)
		{
			max_x_.clear();
			max_x_.push_back(current);
		}

		for (auto iter = blocks_graph_[current].begin(); iter != blocks_graph_[current].end(); ++iter) // Для каждого ребра
		{
			point_t &next = *iter;
			if (visited_.find(next) == visited_.end())
				DFS(next); // Запускаемся из соседа		
		}
	};
	void forming_dir(std::string &turn)
	{
		if (turn == "left")
		{
			if (dp_.x == 0)
			{
				dir_.x = (-dp_.y);
				dir_.y = (-dp_.x);
			}
			if (dp_.x != 0)
			{
				dir_.x = dp_.y;
				dir_.y = dp_.x;
			}
		}
		if (turn == "right")
		{
			if (dp_.x == 0)
			{
				dir_.x = dp_.y;
				dir_.y = dp_.x;
			}
			if (dp_.x != 0)
			{
				dir_.x = (-dp_.y);
				dir_.y = (-dp_.x);
			}
		}
	};	
	int set_color_tab(sf::Color &color)
	{
		int hue_lightness = 0;

		if ((color.r == 255) || (color.g == 255) || (color.b == 255))//формирование оттенка
		{
			if ((color.r == 12) || (color.g == 12) || (color.b == 12))
				hue_lightness = 10;//самый светлый цвет
			else
				hue_lightness = 20;//средний
		}
		else
			hue_lightness = 30;//тёмный

		//далее поиск конкретного цвета
		if (color.g == color.b)
		{
			if ((hue_lightness == 10) && (color.g == 255))
				hue_lightness += 3;//голубой
			else
				hue_lightness += 6;//красный
		}
		else if (color.r == color.g)
		{
			if ((hue_lightness == 10) && (color.r == 255))
				hue_lightness += 5;//жёлтый
			else
				hue_lightness += 2;//синий
		}
		else if (color.r == color.b)
		{
			if ((hue_lightness == 10) && (color.r == 12))
				hue_lightness += 4;//зелёный
			else
				hue_lightness += 1;//фиолетовый
		}
		return hue_lightness;
	};
	void final_point(int &step_att)
	{
		point_t dir = dir_;
		auto find_point = std::max_element(max_x_.begin(), max_x_.end(),//что с max??
			[dir](point_t const &a, point_t const &b)
		{
			return direct_compare(a, b, dir) < 0;
		});

		if ((find_point->x + dp_.x <= code_hard_.getSize().x) && (find_point->y + dp_.y <= code_hard_.getSize().y))
		{
			point_t next(find_point->x + dp_.x, find_point->y + dp_.y);
			sf::Color color_next = code_hard_.getPixel(next.x, next.y);
			if ((color_next.r == 0) && (color_next.g == 0) && (color_next.b == 0))//если чёрный, то конец программы
			{
				if (step_att <= 8)
				{
					if (step_att % 2 == 0)
					{
						if (cc_ == "right")
							cc_ = "left";
						else
							cc_ = "right";
						step_att++;
						final_point(step_att);
					}
					else
					{
						std::string turn_ = "right";
						forming_dir(turn_);
						dp_ = dir_;
						forming_dir(cc_);
						step_att++;
						final_point(step_att);
					}
				}
				if (step_att == 8)
				{
					end_program = true;
					pos_ = next;
				}
			}
			else
			{
				step_att = 0;
				pos_ = next;
			}
		}
		std::cout << find_point->x << " - " << find_point->y << "\n";
	};
	void action(hue_lightness_t const &color_change)
	{	
		actions_map_[color_change]();//вызов нужной функции из map
	};

	void empty_ac()
	{
		std::cout << "";
	};
	void add()
	{
		if (stack_prog_.size() > 1)
		{
			int mod_stack = (stack_prog_[stack_prog_.size() - 2] + stack_prog_[stack_prog_.size() - 1]);
			stack_prog_.pop_back();
			stack_prog_.pop_back();
			stack_prog_.push_back(mod_stack);
		}
	};
	void substract()
	{
		if (stack_prog_.size() > 1)
		{
			int mod_stack = (stack_prog_[stack_prog_.size() - 2] - stack_prog_[stack_prog_.size() - 1]);
			stack_prog_.pop_back();
			stack_prog_.pop_back();
			stack_prog_.push_back(mod_stack);
		}
	};
	void push()
	{
		stack_prog_.push_back(visited_.size()); 
	};
	void pop()
	{
		if (stack_prog_.size() != 0)
			stack_prog_.pop_back();
	};
	void multiply()
	{
		if (stack_prog_.size() > 1)
		{
			int mod_stack = (stack_prog_[stack_prog_.size() - 2] * stack_prog_[stack_prog_.size() - 1]);
			stack_prog_.pop_back();
			stack_prog_.pop_back();
			stack_prog_.push_back(mod_stack);
		}
	};
	void divide()
	{
		if (stack_prog_.size() > 1)
		{
			int mod_stack = (stack_prog_[stack_prog_.size() - 2] / stack_prog_[stack_prog_.size() - 1]);
			stack_prog_.pop_back();
			stack_prog_.pop_back();
			stack_prog_.push_back(mod_stack);
		}
	};
	void mod()
	{
		if (stack_prog_.size() > 1)
		{
			int mod_stack = (stack_prog_[stack_prog_.size() - 2] % stack_prog_[stack_prog_.size() - 1]);
			stack_prog_.pop_back();
			stack_prog_.pop_back();
			stack_prog_.push_back(mod_stack);
		}
	};
	void not()
	{
		if (stack_prog_.size() != 0)
		{
			if (stack_prog_[stack_prog_.size() - 1] == 0)
				stack_prog_[stack_prog_.size() - 1] = 1;
			else
				stack_prog_[stack_prog_.size() - 1] = 0;
		}
	};
	void greater()
	{
		if (stack_prog_.size() != 0)
			if (stack_prog_.size() > 1)
			{
				if (stack_prog_[stack_prog_.size() - 2] > stack_prog_[stack_prog_.size()] - 1)
				{	
					stack_prog_.pop_back();
					stack_prog_.pop_back();
					stack_prog_.push_back(1);
				}
				else
				{
					stack_prog_.pop_back();
					stack_prog_.pop_back();
					stack_prog_.push_back(0);
				}
			}
	};
	void pointer()
	{
		if (stack_prog_.size() != 0)
		{
			point_t dir;
			std::string direction;
			if ((stack_prog_[stack_prog_.size()] - 1) < 0)
				direction = "left";
			else
				direction = "right";
			forming_dir(direction);
			dp_ = dir;
			forming_dir(direction);
		}
	};
	void switch_array()
	{
		if (stack_prog_.size() != 0)
		{
			int modulo = (stack_prog_[stack_prog_.size() - 1] % 2);
			if (modulo != 0)
			{
				if (cc_ == "left")
					cc_ = "right";
				else
					cc_ = "left";
			}
			stack_prog_.pop_back();
		}
	};
	void duplicate()
	{
		if (stack_prog_.size() != 0)
		{
			int duplicated = stack_prog_[stack_prog_.size() - 1];
			stack_prog_.push_back(duplicated);
		}
	};
	void roll()
	{
		if (stack_prog_.size() != 0)
		{
			int m = stack_prog_[stack_prog_.size() - 1];
			int n = stack_prog_[stack_prog_.size() - 2];
			if (n >= 0)
			{
				if (m > 0)
				{
					for (int i = 0; i < m; ++i)
					{
						int temp_str = stack_prog_[stack_prog_.size() - 1];

						for (int id = 0; id < n; ++id)
						{
							stack_prog_[stack_prog_.size() - 1 - id] = stack_prog_[stack_prog_.size() - 2 - id];
						}
						stack_prog_[stack_prog_.size() - 1 - n] = temp_str;
					}
				}
				else
				{
					for (int i = 0; i > m; --i)
					{
						int temp_str = stack_prog_[stack_prog_.size() - 1];

						for (int id = 0; id < n; ++id)
						{
							stack_prog_[stack_prog_.size() - 1 - id] = stack_prog_[stack_prog_.size() - 2 - id];
						}
						stack_prog_[stack_prog_.size() - 1 - n] = temp_str;
					}
				}
			}
		}
	};
	void in_int()
	{
		int input_num;
		std::cin >> input_num;
		stack_prog_.push_back(input_num);
	};
	void in_char()
	{
		char word;
		std::cin >> word;
		if (std::isalpha((unsigned char)word))
		{
			int alp_in_numb = (char)tolower(word) - 'a';
			stack_prog_.push_back(alp_in_numb);
		}
	};
	void out_int()
	{
		if (stack_prog_.size() != 0)
		{
			std::cout << stack_prog_[stack_prog_.size() - 1] << std::endl;
			stack_prog_.pop_back();
		}
	};
	void out_char()
	{
		if (stack_prog_.size() != 0)
		{
			char alp_in_numb = stack_prog_[stack_prog_.size() - 1] + 'a';
			std::cout << alp_in_numb << std::endl;
			stack_prog_.pop_back();
		}
	};

	std::map<hue_lightness_t, action_func_t> actions_map_;
	std::deque<int> stack_prog_;
	
	sf::Image code_hard_;
	std::set<point_t> visited_;
	point_t pos_;
	std::string cc_;
	point_t dp_;
	point_t dir_;
	blocks_graph_t blocks_graph_;
	std::vector<point_t> max_x_;
	bool end_program;
	int step_att;
};

int main()
{
	sf::Image code_hard;
	if (!code_hard.loadFromFile("code.png"))
		return -1;
	Interpretator interp(code_hard);	
	while (!interp.finished())
	{
		interp.step();
	}
	system("pause");
	return 0;
}
