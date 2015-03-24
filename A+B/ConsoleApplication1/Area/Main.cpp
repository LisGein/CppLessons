#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cctype>

typedef std::pair<int, int> list_t;

int main()
{
	
	int num_angles;
	std::ifstream fin("input.txt");
	fin >> num_angles;
	std::vector< std::pair<int, int> > angles(num_angles);
	for (int i = 0; i < num_angles; i++)
	{
		fin >> angles[i].first;
		fin >> angles[i].second;
	}
	double area_polygon = 0;
	for (int i = 0; i < num_angles; i++)
	{
		if (i != num_angles - 1)
			area_polygon += angles[i].first * angles[i + 1].second - angles[i].second  * angles[i + 1].first;

		else
			area_polygon += angles[i].first * angles[0].second - angles[i].second  * angles[0].first;
	}
	area_polygon /= 2.;
	std::cout << area_polygon;
	system("pause");
	return 0;
}