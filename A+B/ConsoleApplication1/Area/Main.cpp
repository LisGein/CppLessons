#include <iostream>
#include <vector>
#include <math.h>
#include <cctype>

typedef std::pair<int, int> list_t;

int main()
{
	
	int num_angles;
	std::cout << "Enter the number of sides" << std::endl;
	std::cin >> num_angles;
	std::vector<list_t> angles(num_angles);
	std::cout << "Enter the coordinates" << std::endl;
	for (int i = 0; i < num_angles; i++)
	{
		std::cin >> angles[i].first;
		std::cin >> angles[i].second;
	}
	double area_polygon = 0;
	for (int i = 0; i < num_angles; i++)
	{
		if (i != num_angles - 1)
			area_polygon += angles[i].first * angles[i + 1].second - angles[i].second  * angles[i + 1].first;

		else
			area_polygon += angles[i].first * angles[0].second - angles[i].second  * angles[0].first;
	}
	area_polygon /= 2;
	std::cout << area_polygon;
	system("pause");
	return 0;
}