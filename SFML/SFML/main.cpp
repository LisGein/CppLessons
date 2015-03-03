#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Random>


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

class rectangle
{
public:
	rectangle();
	
	void draw(sf::RenderWindow &window)
	{
		//window.draw(Rect);
	}
private:
	sf::IntRect Rect;
};

class Ball
{
public:
	Ball(sf::Vector2f const &pos, sf::Vector2f const &speed, float size, sf::Color const &color)
		:speed_(speed),
		Shapes(size),
		size_(size),
		pos_(pos)
	{
		Shapes.setPosition(pos);
		Shapes.setFillColor(color);
	};
	
	void update(float dt)
	{
		if (pos_.y > WINDOW_HEIGHT - size_ * 2)
		{
			speed_ = sf::Vector2f(speed_.x, -abs(speed_.y));//пол
		}
		if (pos_.x > WINDOW_WIDTH - size_ * 2)
		{
			speed_ = sf::Vector2f(-abs(speed_.x), speed_.y);//право
		}

		if (pos_.y < 0) //потолок
		{
			speed_ = sf::Vector2f(speed_.x, abs(speed_.y));
		}
		if (pos_.x < 0) //лево
		{
			speed_ = sf::Vector2f(abs(speed_.x), speed_.y);
		}

			pos_ += speed_ * dt;
			Shapes.setPosition(pos_);
		
	}
	void draw(sf::RenderWindow &window)
	{
		window.draw(Shapes);
	}


private:
	sf::CircleShape Shapes;
	sf::Vector2f speed_;
	sf::Vector2f pos_;
	float size_;
	std::string color_;
	
};

void init_all(std::vector<Ball> &Shapes, std::mt19937 &gen)
{
	std::uniform_real_distribution<float> rect_dist(5, 25);
	int height_rect = rect_dist(gen);
	int wedth_rect = rect_dist(gen);
	sf::IntRect(height_rect, height_rect, wedth_rect, wedth_rect);
	std::uniform_real_distribution<float> x_coor(0.f, WINDOW_WIDTH);




	std::uniform_int_distribution<> color_dist(0, 255);
	std::uniform_real_distribution<float> sp_dist(-300, 300);

	for (int i = 0; i < 30; i++)
	{
		std::uniform_real_distribution<float> size_dist(5, 25);
		float size = size_dist(gen);
		std::uniform_real_distribution<float> x_dist(0.f, WINDOW_WIDTH - 2 * size);
		std::uniform_real_distribution<float> y_dist(0.f, WINDOW_HEIGHT - 2 * size);
		sf::Vector2f pos(x_dist(gen), y_dist(gen));
		sf::Vector2f speed(sp_dist(gen), sp_dist(gen));
		sf::Color color(color_dist(gen), color_dist(gen), color_dist(gen));
		
		Shapes.push_back(Ball(pos, speed, size, color));
	}
}
void draw_all(std::vector<Ball> &Shapes)
{
	for (int i = 0; i < Shapes.size(); ++i)
	{
		Shapes[i].draw(window);
	}

}
void update_all(float &last_up, std::vector<Ball> &Shapes, sf::Clock &clock)
{
	float times = clock.getElapsedTime().asSeconds();
	float dt = static_cast<float>(times - last_up);
	last_up = times;
	for (int i = 0; i < Shapes.size(); ++i)
	{
		Shapes[i].update(dt);
	}
}
int main()
{
	std::random_device rd;
	sf::Clock clock;
	std::vector<Ball> Shapes;
	std::mt19937 gen(rd());
	init_all(Shapes, gen);
	float last_up = clock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		update_all(last_up, Shapes, clock);
		window.clear();
		draw_all(Shapes);
		window.display();
	}
	
	return 0;
}