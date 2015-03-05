#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Random>
const int WINDOW_WIDTH = 1250;
const int WINDOW_HEIGHT = 680;
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

class MovingShape
{
public:
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
};
class Trigl
	:public MovingShape
{
public:
	Trigl(sf::VertexArray const &triangle, sf::Vector2f const &speed, sf::Vector3i const &index)
		:speed_(speed),
		_triangle(triangle),
		index_(index)
	{
	};
	void update(float dt)
	{
		if (pos_1.y > WINDOW_HEIGHT)
			speed_ = sf::Vector2f(speed_.x, -abs(speed_.y));
		if (pos_2.y > WINDOW_HEIGHT)
			speed_ = sf::Vector2f(speed_.x, -abs(speed_.y));
		if (pos_3.y > WINDOW_HEIGHT)
			speed_ = sf::Vector2f(speed_.x, -abs(speed_.y));
		if (pos_1.x > WINDOW_WIDTH)
			speed_ = sf::Vector2f(-abs(speed_.x), speed_.y);
		if (pos_2.x > WINDOW_WIDTH)
			speed_ = sf::Vector2f(-abs(speed_.x), speed_.y);
		if (pos_3.x > WINDOW_WIDTH)
			speed_ = sf::Vector2f(-abs(speed_.x), speed_.y);
		if (pos_1.y < 0)
			speed_ = sf::Vector2f(speed_.x, abs(speed_.y));
		if (pos_2.y < 0)
			speed_ = sf::Vector2f(speed_.x, abs(speed_.y));
		if (pos_3.y < 0)
			speed_ = sf::Vector2f(speed_.x, abs(speed_.y));
		if (pos_1.x< 0)
			speed_ = sf::Vector2f(abs(speed_.x), speed_.y);
		/*if (pos_.y >  WINDOW_HEIGHT - sprite_.getLocalBounds().height)
			speed_ = sf::Vector2f(speed_.x, -abs(speed_.y));//пол
		if (pos_.x > WINDOW_WIDTH - sprite_.getLocalBounds().width)
			speed_ = sf::Vector2f(-abs(speed_.x), speed_.y);//право
		if (pos_.y < 0) //потолок
			speed_ = sf::Vector2f(speed_.x, abs(speed_.y));
		if (pos_.x < 0) //лево
			speed_ = sf::Vector2f(abs(speed_.x), speed_.y);*/

		pos_1 += speed_ * dt;
		pos_2 += speed_ * dt;
		pos_3 += speed_ * dt;

			/*_triangle.resize[index_.x](pos_1.x, pos_1.y);
			_triangle.resize[index_.y](pos_2.x, pos_2.y);
			_triangle.resize[index_.z](pos_3.x, pos_3.y);*/
	}
	void draw(sf::RenderWindow &window)
	{
		window.draw(_triangle);
	}

private:
	sf::Vector2f speed_;
	sf::VertexArray _triangle;
	sf::Vector2f pos_1;
	sf::Vector2f pos_2;
	sf::Vector2f pos_3;
	sf::Vector3i index_;

};

void init_all(std::vector <MovingShape *> &shapes, std::mt19937 &gen, sf::Texture &texture, sf::Texture &texture_)  //определение всех переменных для мячей
{
	std::uniform_int_distribution<> color_dist(0, 255);
	std::uniform_real_distribution<float> sp_dist(-100, 100);
	sf::Vector2f speed(sp_dist(gen), sp_dist(gen));
	for (int i = 0; i < 3; i++)
	{
	//общие:
	sf::Vector2f speed(sp_dist(gen), sp_dist(gen));
	sf::Color color(color_dist(gen), color_dist(gen), color_dist(gen));
	std::uniform_int_distribution<> pos_coor(10, 600);
	int pos_1 = pos_coor(gen);
	int pos_2 = pos_coor(gen);
	int pos_3 = pos_coor(gen);
	sf::Vector2f pos_trigl1(pos_3, pos_1);
	sf::Vector2f pos_trigl2(pos_1, pos_2);
	sf::Vector2f pos_trigl3(pos_2, pos_1);
	sf::Color color1(color_dist(gen), color_dist(gen), color_dist(gen));
	sf::Color color2(color_dist(gen), color_dist(gen), color_dist(gen));
	sf::VertexArray triangle_(sf::Triangles, 3);
	sf::Vector3i index(0, 1, 2);
	triangle_[index.x].position = pos_trigl1;
	triangle_[index.y].position = pos_trigl2;
	triangle_[index.z].position = pos_trigl3;
	triangle_[index.x].color = color;
	triangle_[index.y].color = color1;
	triangle_[index.z].color = color2;

	shapes.push_back(new Trigl(triangle_, speed, index));


	}
}
void draw_all(std::vector <MovingShape *> shapes)
{
	for (int i = 0; i < shapes.size(); ++i)
		shapes[i]->draw(window);
}
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
	sf::Clock clock;
	std::random_device rd;
	std::mt19937 gen(rd());
	sf::Texture texture;
	sf::Texture texture_;
	bool press = false;
	init_all(shapes, gen, texture, texture_);

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

		update_all(last_up, shapes, clock);
		window.clear();
		draw_all(shapes);
		window.display();
	}
	for (int i = 0; i < shapes.size(); ++i)
	{
		delete shapes[i];
	}
	return 0;
}
