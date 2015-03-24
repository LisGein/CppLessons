#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cctype>
#include <Random>
#include <algorithm>
#include <tuple>

struct point_t
{
	point_t()
		:x(0.), y(0.)
	{}
	point_t(double x, double y)
		:x(x), y(y)
	{}
	double x;
	double y;
};

double area_calc(double global_area, int k, int n)
{
	return global_area * k / n;
};

bool intersect(point_t &P, point_t &A, point_t &B)
{
	if (A.x == P.x)
		return A.y < P.y; //маловероятно, но все равно мы не хотим делить на ноль

	if (A.x < P.x && B.x <= P.x || A.x > P.x && B.x >= P.x)
		return false;

	if (A.y > P.y && B.y > P.y)
		return false;

	double k = (A.y - B.y) / (A.x - B.x);
	double b = (A.x * B.y - A.y * B.x) / (A.x - B.x);
	
	return P.y >= k * P.x  + b;
};

bool inside(std::vector<point_t> &vertices, point_t X)
{
	int intersect_count = 0;
	for (size_t coor = 0; coor < vertices.size(); ++coor)
	{
		point_t A = point_t(vertices[coor].x, vertices[coor].y);
		point_t B;
		if (coor != vertices.size() - 1)
			B = point_t(vertices[coor + 1].x, vertices[coor + 1].y);
		else
			B = point_t(vertices[0].x, vertices[0].y);

		if (intersect(X, A, B))
			intersect_count++;
	}

	return intersect_count % 2 != 0;
}

int main()
{
	int num_vert;
	std::ifstream fin("input.txt");
	fin >> num_vert;
	std::vector<point_t> vertices(num_vert);

	for (int i = 0; i < num_vert; i++)
	{
		fin >> vertices[i].x;
		fin >> vertices[i].y;
	}
	
	auto minmax_idx_x = std::minmax_element(vertices.begin(), vertices.end(),
		[](point_t const &a, point_t const &b)
		{
			return a.x < b.x; 
		});
	double min_x = minmax_idx_x.first->x;
	double max_x = minmax_idx_x.second->x;

	auto minmax_idx_y = std::minmax_element(vertices.begin(), vertices.end(),
		[](point_t const &a, point_t const &b)
		{
			return a.y < b.y;
		});
	double min_y = minmax_idx_y.first->y;
	double max_y = minmax_idx_y.second->y;

	size_t num_rd = 100000;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> xcoor(min_x, max_x);
	std::uniform_real_distribution<double> ycoor(min_y, max_y);
	double global_area = (max_x - min_x) * (max_y - min_y);
	int k = 0;

	for (size_t i = 0; i < num_rd; ++i)
	{
		point_t X(xcoor(gen), ycoor(gen));
		if (inside(vertices, X))
			k++;
	}
	std::cout << area_calc(global_area, k, num_rd) << std::endl;
	system("pause");
	return 0;
}