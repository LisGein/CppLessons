#include <iostream>
#include <vector>
#include <math.h>

typedef std::pair <double, double> list_t;
typedef std::pair <int, int> list_int;

int main()
{
	int step = 0;
	int sides = 0;
	double sqrt_area = 0;
	double perimetr = 0;
	double perimetr_by = 0;
	double area_polygon = 0;
	int coor_trigle = 1;
	std::vector<double> side;
	std::vector<double> area_trigles;
	std::vector<double> next_side;
	std::cout << "Enter the number of sides" << std::endl;
	std::cin >> sides;
	std::vector<list_int> coor(sides);
	std::cout << "Enter the coordinates" << std::endl;
	for (int i = 0; i < sides; i++)
	{
		std::cin >> coor[i].first;
		std::cin >> coor[i].second;
	}

	for (int i = 0; i < sides; i++)
	{
		if (i != sides - 1)
		{
			double pow1 = pow((coor[i].first - coor[i + 1].first), 2);
			double pow2 = pow((coor[i].second - coor[i + 1].second), 2);
			side.push_back(abs(sqrt(pow1 + pow2)));
		}
		else
		{
			double pow1 = pow((coor[sides - 1].first - coor[0].first), 2);
			double pow2 = pow((coor[sides - 1].second - coor[0].second), 2);
			side.push_back(abs(sqrt(pow1 + pow2)));
		}
	}
	for (int i = 0; i < sides - 3; ++i)
	{
		double pow1 = pow((coor[2 + i].first - coor[0].first), 2);
		double pow2 = pow((coor[2 + i].second - coor[0].second), 2);
		next_side.push_back(abs(sqrt(pow1 + pow2)));
	}
	if (sides > 3)
		for (int i = 0; i < sides - 2; ++i)
		{
			if (i != sides - 3)
			{
				perimetr = (next_side[step] + side[coor_trigle - 1] + side[coor_trigle]) / 2;
				perimetr_by = abs((perimetr*(perimetr - next_side[step]) * (perimetr - side[coor_trigle - 1]) * (perimetr - side[coor_trigle])));
				sqrt_area = sqrt(perimetr_by);
				area_trigles.push_back(sqrt_area);
				coor_trigle += 2;
				step++;
			}
			else
			{
				perimetr = (next_side[step - 1] + side[coor_trigle - 1] + side[coor_trigle]) / 2;
				perimetr_by = abs((perimetr*(perimetr - next_side[step - 1]) * (perimetr - side[coor_trigle - 1]) * (perimetr - side[coor_trigle])));
				sqrt_area = sqrt(perimetr_by);
				area_trigles.push_back(sqrt_area);
			}
		}	
	else
	{
		perimetr = (side[coor_trigle - 1] + side[coor_trigle] + side[coor_trigle + 1]) / 2;
		perimetr_by = abs((perimetr*(perimetr - side[coor_trigle + 1]) * (perimetr - side[coor_trigle - 1]) * (perimetr - side[coor_trigle])));
		sqrt_area = sqrt(perimetr_by);
		area_trigles.push_back(sqrt_area);
	}
	for (int i = 0; i < area_trigles.size(); i++)
		area_polygon += area_trigles[i];

	std::cout << area_polygon << std::endl;
	system("pause");
	return 0;
}