#include <iostream>
#include <vector>
#include <math.h>
#include <cctype>
#include <Random>

typedef std::pair<int, int> list_int;


std::vector<std::pair<float, float>> set_points(int &global_area, int min_x, int min_y, int max_x, int max_y)
{
	int num_rd = global_area * global_area;
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

void inside(int &intersect_count, int &k)
{
	if (intersect_count % 2 != 0)
		k++;
};
void area_calc(int &global_area, int &k, int &n)
{
	double area = global_area * k / n;
	std::cout << area;
};

void intersect_diag(int &intersect_count, int &A_x, int &A_y, int &B_x, int &B_y, float &X_x, float &X_y, int &min_y)
{
	double A = A_y - B_y;
	double B = B_x - A_x;
	double C = ((A_x * B_y) - (B_x * A_y));
	double D = (X_y - min_y);
	double E = (X_x * min_y) - (X_x * X_y);
	double y = ((((A * E) / D) - C) / B);
	if ((y <= A_y) || (y <= B_y))
		if (y <= X_y)
			intersect_count++;
};

void intersect(std::vector<std::pair<float, float>> &coor_points, std::vector<list_int> &angles, int &min_y, int &global_area)
{
	int n = 0;
	int k = 0;

	for (int i = 0; i < coor_points.size(); ++i)
	{
		n++;
		int intersect_count = 0;
		float X_x = coor_points[i].first;
		float X_y = coor_points[i].second;
		for (int coor = 0; coor < angles.size(); ++coor)
		{
			int A_x = angles[coor].first;
			int A_y = angles[coor].second;
			if (coor != angles.size() - 1)
			{
				int B_x = angles[coor + 1].first;
				int B_y = angles[coor + 1].second;
				if (((A_x < X_x) && (B_x >= X_x)) || ((A_x > X_x) && (B_x <= X_x)))//если А справа, а В слева или
				{
					if ((A_y <= X_y) && (B_y <= X_y))//если прямая ниже точки
						intersect_count++;
					else if (((A_y > X_y) && (B_y <= X_y)) || ((A_y < X_y) && (B_y >= X_y)))//если А выше, а В ниже или В выше, а А ниже
						intersect_diag(intersect_count, A_x, A_y, B_x, B_y, X_x, X_y, min_y);		
				}
				else if ((A_x == X_x) && (B_x == X_x))
					intersect_count++;
			}

			else
			{
				int B_x = angles[0].first;
				int B_y = angles[0].second;

				if (((A_x < X_x) && (B_x >= X_x)) || ((A_x > X_x) && (B_x <= X_x)))//если А справа, а В слева или
				{
					if ((A_y <= X_y) && (B_y <= X_y))//если прямая ниже точки			
						intersect_count++;
					else if (((A_y > X_y) && (B_y <= X_y)) || ((A_y < X_y) && (B_y >= X_y)))//если А выше, а В ниже или В выше, а А ниже					
						intersect_diag(intersect_count, A_x, A_y, B_x, B_y, X_x, X_y, min_y);					
				}
				else if ((A_x == X_x) && (B_x == X_x))
					intersect_count++;
			}
		}
		inside(intersect_count, k);
	}
	area_calc(global_area, k, n);
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
	std::vector<std::pair<float, float>> coor_points = set_points(global_area, min_x, min_y, max_x, max_y);
	intersect(coor_points, angles, min_y, global_area);
	system("pause");
	return 0;
}