#include <SFML/Graphics.hpp>
#include <vector>


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");


class Ball
{
public:
	Ball(sf::Vector2f const &pos, sf::Vector2f const &speed, float size, std::string color)
		:speed_(speed),
		size_(size),
		color_(color),
		pos_(pos)
	{
		Shapes.setPosition(pos);
	};
	
	void update(float dt)
	{
		
			if (pos_.y >= WINDOW_HEIGHT)
				{
					speed_ = - speed_ * dt;
				}

			speed_ = speed_ * dt;

			Shapes.move(speed_.x * dt, speed_.y * dt);
		
	}
	void draw(sf::RenderWindow &window)
	{
		window.draw(Shapes);
	}


private:
	sf::CircleShape Shapes;
	sf::Vector2f speed_;
	sf::Vector2f const pos_;
	float size_;
	std::string color_;
	
};

void init_all(std::vector<Ball> &Shapes)
{
	sf::Vector2f pos(0, 0);
	sf::Vector2f speed(50, 50);
	float size(20.f);
	std::string color("Green");
	Shapes.push_back(Ball(pos,speed,size,color));
	//sf::Vector2f pos(640, 480);
	//sf::Vector2f speed(-50, -50);
	//float size(25.f);
	//std::string color("Blue");
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
		draw_all(Shapes);
		window.display();
	}
	
	return 0;
}