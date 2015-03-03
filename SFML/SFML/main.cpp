#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Random>


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

class rectanglss
{
public:
	rectanglss(sf::Vector2f const &pos, sf::Vector2f const &size, sf::Color const &color)
		:Rect_(size),
		size_(size),
		pos_(pos)
	{
		Rect_.setPosition(pos);
		Rect_.setFillColor(color);
		
	};
	
	void _draw(sf::RenderWindow &window)
	{
		window.draw(Rect_);
	}

private:
	sf::RectangleShape Rect_;
	sf::Vector2i pos_;
	sf::Vector2i size_;
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
void init_rect(std::vector<rectanglss> &Rect, std::mt19937 &gen)
{
	std::uniform_real_distribution<float> rect_dist_x(40, 80);
	std::uniform_real_distribution<float> rect_dist_y(20, 40);
	std::uniform_int_distribution<> color_dist(0, 255);
	std::uniform_real_distribution<float> x_coor(0.f, WINDOW_WIDTH);
	for (int i = 0; i < 30; i++)
	{
		sf::Color color(color_dist(gen), color_dist(gen), color_dist(gen));
		sf::Vector2f pos(x_coor(gen), x_coor(gen));
		sf::Vector2f size(rect_dist_x(gen), rect_dist_y(gen));
		Rect.push_back(rectanglss(pos, size, color));
	}
}
void draw_rect(std::vector<rectanglss> &Rect_)
{
	for (int i = 0; i < Rect_.size(); ++i)
	{
		Rect_[i]._draw(window);
	}
}
void init_all(std::vector<Ball> &Shapes, std::mt19937 &gen)
{


	std::uniform_int_distribution<> color_dist(0, 255);
	std::uniform_real_distribution<float> sp_dist(-100, 100);

	for (int i = 0; i < 30; i++)
	{
		std::uniform_real_distribution<float> size_dist(5, 10);
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
	std::vector<rectanglss> Rect_;
	std::random_device rd;
	sf::Clock clock;
	std::vector<Ball> Shapes;
	std::mt19937 gen(rd());
	init_rect(Rect_, gen);
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
		draw_rect(Rect_);
		draw_all(Shapes);
		window.display();
	}
	
	return 0;
}