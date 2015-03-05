#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Random>



const int WINDOW_WIDTH = 200;
const int WINDOW_HEIGHT = 200;
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

class Obj
{
public:
	virtual void draw(sf::RenderWindow &window) = 0;
};

class Rectangle  //класс - прямоугольник
	:public Obj
{
public:
	Rectangle(sf::Vector2f const &pos, sf::Vector2f const &size, sf::Color const &color)
		:rect_(size),
		size_(size),
		pos_(pos)
	{
		rect_.setPosition(pos);
		rect_.setFillColor(color);
	};
	void draw(sf::RenderWindow &window)
	{
		window.draw(rect_);
	}
private:
	sf::RectangleShape rect_;
	sf::Vector2f pos_;
	sf::Vector2f size_;
	sf::Vector2f speed_;
};


class MovingShape
{
public:
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void on_key_pressed(sf::Keyboard::Key const &code, bool press) = 0;
};

class zmei
	:public MovingShape
{
public:
	zmei(sf::Vector2f const &pos, sf::Vector2f const &speed, sf::Vector2f const &size, sf::Color const &color, sf::Vector2f const &posObj_)
		:speed_(speed),
		rect_(size),
		size_(size),
		pos_(pos),
		speedtest(speed_),
		posObj(posObj_)
	{
		rect_.setPosition(pos);
		rect_.setFillColor(color);
	};
	void update(float dt)
	{
		if (pos_.y >  WINDOW_HEIGHT - rect_.getLocalBounds().height)
			speed_ = sf::Vector2f(speed_.x, -abs(speed_.y));//пол
		if (pos_.x > WINDOW_WIDTH - rect_.getLocalBounds().width)
			speed_ = sf::Vector2f(-abs(speed_.x), speed_.y);//право
		if (pos_.y < 0) //потолок
			speed_ = sf::Vector2f(speed_.x, abs(speed_.y));
		if (pos_.x < 0) //лево
			speed_ = sf::Vector2f(abs(speed_.x), speed_.y);

		pos_ += speed_ * dt;
		rect_.setPosition(pos_);
		if ((posObj.x == pos_.x) && (posObj.y == pos_.y))
		{
			std::cout << "1";
		}

	}
	void draw(sf::RenderWindow &window)
	{
		window.draw(rect_);
	}
	void on_key_pressed(sf::Keyboard::Key const &code, bool press)
	{

		if (press){
			int speed_value = 5;
			if (code == sf::Keyboard::Up)
				speed_ = sf::Vector2f(0, -abs(speed_value * speedtest.y));
			if (code == sf::Keyboard::Down)
				speed_ = sf::Vector2f(0, abs(speed_value * speedtest.y));
			if (code == sf::Keyboard::Right)
				speed_ = sf::Vector2f(abs(speed_value * speedtest.x), 0);
			if (code == sf::Keyboard::Left)
				speed_ = sf::Vector2f(-abs(speed_value * speedtest.x), 0);
		}
		if (!press){
			if (code == sf::Keyboard::Up)
				speed_ = sf::Vector2f(0, -abs(speedtest.y));
			if (code == sf::Keyboard::Down)
				speed_ = sf::Vector2f(0, abs(speedtest.y));
			if (code == sf::Keyboard::Right)
				speed_ = sf::Vector2f(abs(speedtest.x), 0);
			if (code == sf::Keyboard::Left)
				speed_ = sf::Vector2f(-abs(speedtest.x), 0);
		}
	}
	private:
		sf::RectangleShape rect_;
		sf::Vector2f pos_;
		sf::Vector2f posObj;
		sf::Vector2f size_;
		sf::Vector2f speed_;
		sf::Vector2f speedtest;
		sf::Vector2f acceleration_;

	};

class Sprite  // класс - sprite
	:public MovingShape
{
public:
	Sprite(sf::Vector2f const &pos, sf::Vector2f const &speed, sf::Texture &texture)
		:speed_(speed),
		pos_(pos),
		speedtest(speed_)
	{
		sprite_.setPosition(pos);
		sprite_.setTexture(texture);
	};
	void update(float dt)
	{
		if (pos_.y >  WINDOW_HEIGHT - sprite_.getLocalBounds().height)
			speed_ = sf::Vector2f(speed_.x, -abs(speed_.y));//пол
		if (pos_.x > WINDOW_WIDTH - sprite_.getLocalBounds().width)
			speed_ = sf::Vector2f(-abs(speed_.x), speed_.y);//право
		if (pos_.y < 0) //потолок
			speed_ = sf::Vector2f(speed_.x, abs(speed_.y));
		if (pos_.x < 0) //лево
			speed_ = sf::Vector2f(abs(speed_.x), speed_.y);

		pos_ += speed_ * dt;
		sprite_.setPosition(pos_);

	}
	void draw(sf::RenderWindow &window)
	{
		window.draw(sprite_);
	}
	void on_key_pressed(sf::Keyboard::Key const &code, bool press)
	{

		if (press){
			int speed_value = 15;
			if (code == sf::Keyboard::Up)
				speed_ = sf::Vector2f(0, -abs(speed_value * speedtest.y));
			if (code == sf::Keyboard::Down)
				speed_ = sf::Vector2f(0, abs(speed_value * speedtest.y));
			if (code == sf::Keyboard::Right)
				speed_ = sf::Vector2f(abs(speed_value * speedtest.x), 0);
			if (code == sf::Keyboard::Left)
				speed_ = sf::Vector2f(-abs(speed_value * speedtest.x), 0);
		}
		if (!press){
			int speed_value = 15;
			if (code == sf::Keyboard::Up)
				speed_ = sf::Vector2f(0, -abs(speedtest.y));
			if (code == sf::Keyboard::Down)
				speed_ = sf::Vector2f(0, abs(speedtest.y));
			if (code == sf::Keyboard::Right)
				speed_ = sf::Vector2f(abs(speedtest.x), 0);
			if (code == sf::Keyboard::Left)
				speed_ = sf::Vector2f(-abs(speedtest.x), 0);
		}
	}
private:
	sf::Sprite sprite_;
	sf::Vector2f pos_;
	sf::Vector2f speed_;
	sf::Event event;
	sf::Vector2f speedtest;
	sf::Vector2f acceleration_;
};
void init_all(std::vector <Obj *> &rect, std::vector <MovingShape *> &shapes, std::mt19937 &gen, sf::Texture &texture)  //определение всех переменных для мячей
{
	
	//объекты
	sf::Vector2f size(25, 25);

	std::uniform_real_distribution<float> x_coor(0.f, WINDOW_WIDTH - size.x);
	std::uniform_real_distribution<float> y_coor(0.f, WINDOW_HEIGHT - size.y);
	sf::Vector2f pos_(x_coor(gen), y_coor(gen));
	std::uniform_int_distribution<> color_dist(0, 255);
	sf::Color color_(color_dist(gen), color_dist(gen), color_dist(gen));
	
	//печенька
	sf::Vector2f pos = pos_;
	std::uniform_real_distribution<float> sp_dist(5, 10);
	sf::Vector2f speed(sp_dist(gen), sp_dist(gen));
	
	sf::Vector2f _pos(0, 0);
	sf::Color _color(10,100,250);
	shapes.push_back(new zmei(_pos, speed, size, _color, pos));
	rect.push_back(new Rectangle(pos, size, color_));

}
void draw_all(std::vector <MovingShape *> shapes, std::vector <Obj *> &rect)
{
	for (int i = 0; i < shapes.size(); ++i)
	
		shapes[i]->draw(window);
	for (int i = 0; i < rect.size(); ++i)
		rect[i]->draw(window);

}
void on_key_pressed(std::vector <MovingShape *> shapes, sf::Keyboard::Key const &code, bool press)
{

	for (int i = 0; i < shapes.size(); ++i)
		shapes[i]->on_key_pressed(code, press);
};
void update_all(float &last_up, std::vector <MovingShape *> shapes, sf::Clock &clock)
{
	float times = clock.getElapsedTime().asSeconds();
	float dt = static_cast<float>(times - last_up);
	last_up = times;
	for (int i = 0; i < shapes.size(); ++i)
		shapes[i]->update(dt);
}
int main()
{
	std::vector <MovingShape *> shapes;
	std::vector <Obj *> rect;
	sf::Clock clock;
	std::random_device rd;
	std::mt19937 gen(rd());
	sf::Texture texture;
	bool press = false;
	init_all(rect,shapes, gen, texture);

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

			on_key_pressed(shapes, event.key.code, press);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		update_all(last_up, shapes, clock);
		window.clear();
		draw_all(shapes,rect);
		window.display();
	}
	for (int i = 0; i < shapes.size(); ++i)
	{
		delete shapes[i];
	}
	return 0;
}
