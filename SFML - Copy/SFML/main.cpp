#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");


class Ball
{
public:
	Ball(sf::Vector2f const &pos, sf::Vector2f const &speed, float size, sf::Color const &color)
		:speed_(speed),
		Shapes(size),
		size_(size)
		

		
	{
		Shapes.setPosition(pos);
		Shapes.move(speed_);
		//Shapes.setRadius(size_);
		Shapes.setFillColor(color);
	};
	
	void update(float dt)
	{
		sf::Vector2f pos_ = Shapes.getPosition();
		if (pos_.y >= WINDOW_HEIGHT - size_ * 2)
		{
			speed_ = sf::Vector2f(speed_.x, -speed_.y);//пол
		}
		if (pos_.x >= WINDOW_WIDTH - size_ * 2)
		{
			speed_ = sf::Vector2f(-speed_.x, speed_.y);//право
		}

		if (pos_.y <= 0) //потолок
		{
			speed_ = sf::Vector2f(speed_.x, -speed_.y);
		}
		if (pos_.x <= 0) //лево
		{
			speed_ = sf::Vector2f(-speed_.x, speed_.y);
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

void init_all(std::vector<Ball> &Shapes)
{
	sf::Vector2f pos(0, 0);
	sf::Vector2f speed (50, 50);
	float size(20);
	sf::Color color = sf::Color::Blue;
	Shapes.push_back(Ball(pos,speed,size,color));
	//pos = sf::Vector2f(640, 480);
	//speed = sf::Vector2f(-50, -50);
	//float size(25.f);
	//sf::Color color = sf::Color::Green;
	//Shapes.push_back(Ball(pos,speed,size,color));
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
	sf::Clock clock;
	std::vector<Ball> Shapes;
	init_all(Shapes);
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