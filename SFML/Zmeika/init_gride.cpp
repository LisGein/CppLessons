#include "init_gride.h"
#include "global.h"

void init_gride(std::vector<Gride> &lines)  //определение всех переменных для мячей
{
	int sum_line_x = (WINDOW_WIDTH / pix);//количество линий по х
	int sum_line_y = (WINDOW_HEIGHT / pix);//по y
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
		lines.push_back(Gride(line));
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
		lines.push_back(Gride(line_));
		line_y += 30;
	}
}