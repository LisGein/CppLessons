#include <SFML/Graphics.hpp>
class MovingShape
{
public:
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void on_key_pressed(sf::Keyboard::Key const &code, bool press) = 0;
};