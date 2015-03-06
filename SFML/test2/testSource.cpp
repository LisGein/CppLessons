#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Random>
const int WINDOW_WIDTH = 300;
const int WINDOW_HEIGHT = 300;
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

class MovingShape
{
public:
	virtual void draw(sf::RenderWindow &window) = 0;
};
class Gride
	:public MovingShape
{
public:
	Gride(sf::VertexArray const &triangle)
		:_triangle(triangle)
	{
	};
	
	void draw(sf::RenderWindow &window)
	{
		window.draw(_triangle);
	}

private:
	sf::VertexArray _triangle;
};

void init_all(std::vector <MovingShape *> &lines, std::mt19937 &gen)  //определение всех переменных для мячей
{
	int sum_line_x = (WINDOW_WIDTH / 30);//количество линий по х
	int sum_line_y = (WINDOW_HEIGHT / 30);//по y
	int line_x = 0;
	int line_y = 0;

	for (int i = 0; i < sum_line_x; i++)
	{
	int pos_1 = line_x;
	int pos_2 = 0;
	int pos_3 = WINDOW_WIDTH;
	sf::Vector2f pos_trigl1(pos_1, pos_2);
	sf::Vector2f pos_trigl2(pos_1, pos_3);
	sf::VertexArray line(sf::Lines, 2);
	sf::Vector3i index(0, 1, 2);
	line[index.x].position = pos_trigl1;
	line[index.y].position = pos_trigl2;
	lines.push_back(new Gride(line));
	line_x += 30;
	}
	for (int i = 0; i < sum_line_y; i++)
	{
		int pos_1_ = line_y;
		int pos_2_ = 0;
		int pos_3_ = WINDOW_HEIGHT;
		sf::Vector2f pos_trigl1(pos_2_, pos_1_);
		sf::Vector2f pos_trigl2(pos_3_, pos_1_);
		sf::VertexArray line_(sf::Lines, 2);
		sf::Vector3i index(0, 1, 2);
		line_[index.x].position = pos_trigl1;
		line_[index.y].position = pos_trigl2;
		lines.push_back(new Gride(line_));
		line_y += 30;
	}
}
void draw_all(std::vector <MovingShape *> lines)
{
	for (int i = 0; i < lines.size(); ++i)
		lines[i]->draw(window);
}

int main()
{
	std::vector <MovingShape *> lines;
	sf::Clock clock;
	std::random_device rd;
	std::mt19937 gen(rd());
	bool press = false;
	init_all(lines, gen);

	float last_up = clock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
				press = true;
			if (event.type == sf::Event::KeyReleased)
				press = false;

		

			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		draw_all(lines);
		window.display();
	}
	return 0;
}
