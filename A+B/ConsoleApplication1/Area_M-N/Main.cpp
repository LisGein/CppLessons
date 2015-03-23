#include <iostream>
#include <vector>
#include <math.h>
#include <cctype>
#include <Random>

typedef std::pair<int, int> list_int;
typedef std::pair<float, float> list_f;

std::vector<std::pair<float, float>> set_points(int &global_area, int min_x, int min_y, int max_x, int max_y)
{
	int num_rd = global_area;
	if (global_area < 1000)
		num_rd *= global_area;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::vector<std::pair<float, float>> points(num_rd);
	for (int i = 0; i < num_rd; ++i)
	{
		std::uniform_real_distribution<float> xcoor(min_x, max_x);
		std::uniform_real_distribution<float> ycoor(min_y, max_y);
		points[i].first = xcoor(gen);
		points[i].second = ycoor(gen);
	}
	return points;
};

void area_calc(int &global_area, int &k, int &n)
{
	double area = global_area * k / n;
	std::cout << area;
};

int intersect(std::pair<float, float> &X_coor, list_int &A_coor,list_int &B_coor, int &min, int &intersect_count)
{
	if (((A_coor.first < X_coor.first) && (B_coor.first >= X_coor.first)) || ((A_coor.first > X_coor.first) && B_coor.first <= X_coor.first))//если А справа, а В слева или
		{
			if ((A_coor.second <= X_coor.second) && (B_coor.second <= X_coor.second))//если прямая ниже точки
				intersect_count++;
			else if (((A_coor.second > X_coor.second) && (B_coor.second <= X_coor.second)) || ((A_coor.second < X_coor.second) && (B_coor.second >= X_coor.second)))//если А выше, а В ниже или В выше, а А ниже
			{
				double A = A_coor.second - B_coor.second;
				double B = B_coor.first - A_coor.first;
				double C = ((A_coor.first * B_coor.second) - (B_coor.first * A_coor.second));
				double D = (X_coor.second - min);
				double E = (X_coor.first * min) - (X_coor.first * X_coor.second);
				double y = ((((A * E) / D) - C) / B);
				if ((y <= A_coor.second) || (y <= B_coor.second))
					if (y <= X_coor.second)
						intersect_count++;
			}
		}
	else if ((A_coor.first == X_coor.first) && (B_coor.first == X_coor.first))
			intersect_count++;
	return intersect_count;
};

int main()
{
	int num_angles;
	std::cout << "Enter the number of sides" << std::endl;
	std::cin >> num_angles;
	std::vector<list_int> angles(num_angles);
	std::cout << "Enter the coordinates" << std::endl;
	for (int i = 0; i < num_angles; i++)
	{
		std::cin >> angles[i].first;
		std::cin >> angles[i].second;
	}
	int min_x = angles[0].first;
	int max_x = 0;
	int min_y = angles[0].second;
	int max_y = 0;
	for (int i = 0; i < angles.size(); i++)
	{
		if (angles[i].first < min_x)
			min_x = angles[i].first;
		if (angles[i].first > max_x)
			max_x = angles[i].first;
		if (angles[i].second < min_y)
			min_y = angles[i].second;
		if (angles[i].second > max_y)
			max_y = angles[i].second;
	}
	min_x--;
	max_x++;
	min_y--;
	max_y++;

	int global_area = (max_x - min_x)* (max_y - min_y);
	std::vector<list_f> coor_points = set_points(global_area, min_x, min_y, max_x, max_y);
	list_f X_coor;
	list_int A_coor;
	list_int B_coor;
	int n = 0;
	int k = 0;

	for (int i = 0; i < coor_points.size(); ++i)
	{
		n++;
		int intersect_count = 0;
		X_coor = std::make_pair(coor_points[i].first, coor_points[i].second);
		for (int coor = 0; coor < angles.size(); ++coor)
		{
			A_coor = std::make_pair(angles[coor].first, angles[coor].second);
			if (coor != angles.size() - 1)
			{
				B_coor = std::make_pair(angles[coor + 1].first, angles[coor + 1].second);
				intersect(X_coor, A_coor, B_coor, min_y, intersect_count);
			}
			else
			{
				B_coor = std::make_pair(angles[0].first, angles[0].second);
				intersect(X_coor, A_coor, B_coor, min_y, intersect_count);
			}
		}
		if (intersect_count % 2 != 0)
			k++;
	}
	area_calc(global_area, k, n);
	system("pause");
	return 0;
}