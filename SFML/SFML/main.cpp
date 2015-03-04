#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Random>


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

class MovingShape
{
public:
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
};




class Rectangle  //класс - прямоугольник
	//:public MovingShape
{
public:
	Rectangle(sf::Vector2f const &pos, sf::Vector2f const &size, sf::Color const &color, sf::Vector2f const &speed)
		:speed_(speed), 
		rect_(size),
		size_(size),
		pos_(pos)
	{
		rect_.setPosition(pos);
		rect_.setFillColor(color);
		
	};
	
	void _draw(sf::RenderWindow &window)
	{
		window.draw(rect_);
	}

private:
	sf::RectangleShape rect_;
	sf::Vector2i pos_;
	sf::Vector2i size_;
	sf::Vector2f speed_;
};

class Ball  // класс - мяч
	:public MovingShape
{
public:
	Ball(sf::Vector2f const &pos, sf::Vector2f const &speed, float size, sf::Color const &color)
		:speed_(speed),
		circle_(size),
		size_(size),
		pos_(pos)
	{
		circle_.setPosition(pos);
		circle_.setFillColor(color);
	};
	
	void update(float dt)
	{
		if (pos_.y > WINDOW_HEIGHT - size_ * 2)
		speed_ = sf::Vector2f(speed_.x, -abs(speed_.y));//пол
		
		if (pos_.x > WINDOW_WIDTH - size_ * 2)
		speed_ = sf::Vector2f(-abs(speed_.x), speed_.y);//право
		
		if (pos_.y < 0) //потолок
		speed_ = sf::Vector2f(speed_.x, abs(speed_.y));
		
		if (pos_.x < 0) //лево
		speed_ = sf::Vector2f(abs(speed_.x), speed_.y);
		
		pos_ += speed_ * dt;
		circle_.setPosition(pos_);	
	}
	void draw(sf::RenderWindow &window)
	{
		window.draw(circle_);
	}


private:
	sf::CircleShape circle_;
	sf::Vector2f speed_;
	sf::Vector2f pos_;
	float size_;
};
void init_rect(std::vector<Rectangle> &rect_, std::mt19937 &gen)  //определение всех переменных для прямоугольников
{
	std::uniform_real_distribution<float> rect_dist_x(40, 80);
	std::uniform_real_distribution<float> rect_dist_y(20, 40);
	std::uniform_int_distribution<> color_dist(0, 255);
	std::uniform_real_distribution<float> x_coor(0.f, WINDOW_WIDTH);
	std::uniform_real_distribution<float> sp_dist(-100, 100);
	for (int i = 0; i < 30; i++)
	{
		sf::Color color(color_dist(gen), color_dist(gen), color_dist(gen));
		sf::Vector2f pos(x_coor(gen), x_coor(gen));
		sf::Vector2f size(rect_dist_x(gen), rect_dist_y(gen));
		sf::Vector2f speed(sp_dist(gen), sp_dist(gen));
		rect_.push_back(Rectangle(pos, size, color, speed));
	}
}
void draw_rect(std::vector<Rectangle> &rect_)
{
	for (int i = 0; i < rect_.size(); ++i)
	{
		rect_[i]._draw(window);
	}
}
void init_shape(std::vector <MovingShape *> shapes, std::mt19937 &gen)  //определение всех переменных для мячей
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
		//MovingShape * shape = new Ball(pos, speed, size, color);
		//circle_.push_back(Ball(pos, speed, size, color));
		shapes.push_back(new Ball(pos, speed, size, color));


	}
}
void draw_circle(std::vector <MovingShape *> shapes)
{
	
	for (int i = 0; i < shapes.size(); ++i)
	{
		shapes[i]->draw(window);
	}

}
void update_all(float &last_up, std::vector <MovingShape *> shapes, sf::Clock &clock)
{
	float times = clock.getElapsedTime().asSeconds();
	float dt = static_cast<float>(times - last_up);
	last_up = times;
	for (int i = 0; i < shapes.size(); ++i)
	{
		shapes[i] -> update(dt);
	}
}
int main()
{
	std::vector <MovingShape *> shapes;
	std::vector<Rectangle> rect_;
	std::random_device rd;
	sf::Clock clock;
	std::vector<Ball> circle_;
	std::mt19937 gen(rd());
	init_rect(rect_, gen);
	init_shape(shapes, gen);

	float last_up = clock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		update_all(last_up, shapes, clock);
		window.clear();
		draw_rect(rect_);

		draw_circle(shapes);
		window.display();
	}
	for (int i = 0; i < shapes.size(); ++i)
	{
		delete shapes[i];
	}
	return 0;
}