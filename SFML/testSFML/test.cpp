#include <SFML/Graphics.hpp>
#include <vector>
#include <Random>
#include <deque>
#include <iterator>

const float pix = 30;
const int WINDOW_WIDTH = 300;
const int WINDOW_HEIGHT = 300;
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

class zmei
{
private:
	struct SnakeSegment
	{
		SnakeSegment(sf::Vector2f pos_)
			:pos(pos_)
			,rect(sf::Vector2f(pix, pix))
		{
			rect.setPosition(pos.x * pix, pos.y * pix);
		}
		sf::Vector2i pos;
		sf::RectangleShape rect;
	};
	std::deque<SnakeSegment> queque;
public:
	zmei(sf::Vector2f const &pos, sf::Vector2f const &speed, sf::Vector2f const &size, sf::Color const &color)
		:speed_(speed)
		,size_(size)
		,pos_(pos)
		,next_step(0)
	{
		queque.push_back(pos_);
	};
	void update(float dt)
	{
		next_step = next_step + dt;
		if (next_step >= 0.7)
		{
			if (pos_.y > WINDOW_HEIGHT/pix -2)
				speed_ = sf::Vector2f(speed_.x, -abs(speed_.y));//пол		
			if (pos_.x > WINDOW_WIDTH/pix - 2)
				speed_ = sf::Vector2f(-abs(speed_.x), speed_.y);//право
			if (pos_.y < 1) //потолок
				speed_ = sf::Vector2f(speed_.x, abs(speed_.y));
			if (pos_.x < 1) //лево
				speed_ = sf::Vector2f(abs(speed_.x), speed_.y);
			pos_ += speed_;
			next_step = 0;
			queque.push_back(pos_);
			queque.pop_front();
		}
	}
	void draw(sf::RenderWindow &window)
	{
		for (int i = 0; i < queque.size(); i++)
		{
			window.draw(queque[i].rect);
		}
	}
	void on_key_pressed(sf::Keyboard::Key const &code)
	{
			if (code == sf::Keyboard::Up)
				speed_ = sf::Vector2f(0, -1);
			if (code == sf::Keyboard::Down)
				speed_ = sf::Vector2f(0, 1);
			if (code == sf::Keyboard::Right)
				speed_ = sf::Vector2f(1, 0);
			if (code == sf::Keyboard::Left)
				speed_ = sf::Vector2f(-1, 0);
	}
	private:
		sf::Vector2f pos_;
		sf::Vector2f size_;
		sf::Vector2f speed_;
		float next_step;
	};

void init_all(std::vector <zmei> &shapes, std::mt19937 &gen)
{
	sf::Vector2f size(pix, pix);
	sf::Vector2f speed(1, 0);
	sf::Vector2f _pos(0, 0);
	sf::Color _color(10,100,250);
	shapes.push_back(zmei(_pos, speed, size, _color));
}
void draw_all(std::vector <zmei> &shapes)
{
	for (int i = 0; i < shapes.size(); ++i)	
		shapes[i].draw(window);
}
void on_key_pressed(std::vector <zmei> &shapes, sf::Keyboard::Key const &code)
{
	for (int i = 0; i < shapes.size(); ++i)
		shapes[i].on_key_pressed(code);
};
void update_all(float &last_up, std::vector <zmei> &shapes, sf::Clock &clock)
{
	float times = clock.getElapsedTime().asSeconds();
	float dt = static_cast<float>(times - last_up);
	last_up = times;
	for (int i = 0; i < shapes.size(); ++i)
		shapes[i].update(dt);
}

int main()
{
	std::vector <zmei> shapes;
	sf::Clock clock;
	std::random_device rd;
	std::mt19937 gen(rd());
	init_all(shapes, gen);
	float last_up = clock.getElapsedTime().asSeconds();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				on_key_pressed(shapes, event.key.code);
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}
		update_all(last_up, shapes, clock);
		window.clear();
		draw_all(shapes);
		window.display();
	}
	return 0;
}
