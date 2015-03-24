#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cctype>
#include <Random>

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

std::vector<point_t> gen_rnd_points(double global_area, double min_x, double min_y, double max_x, double max_y)
{
	int num_rd = 100000;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::vector<point_t> points;
	std::uniform_real_distribution<double> xcoor(min_x, max_x);
	std::uniform_real_distribution<double> ycoor(min_y, max_y);
	for (int i = 0; i < num_rd; ++i)
		points.push_back(point_t(xcoor(gen), ycoor(gen)));
	
	return points;
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
	double min_x = vertices[0].x;
	double max_x = vertices[0].x;
	double min_y = vertices[0].y;
	double max_y = vertices[0].y;

	for (size_t i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].x < min_x)
			min_x = vertices[i].x;
		if (vertices[i].x > max_x)
			max_x = vertices[i].x;
		if (vertices[i].y < min_y)
			min_y = vertices[i].y;
		if (vertices[i].y > max_y)
			max_y = vertices[i].y;
	}

	double global_area = (max_x - min_x) * (max_y - min_y);
	std::vector<point_t> rnd_points = gen_rnd_points(global_area, min_x, min_y, max_x, max_y);
	int k = 0;

	for (size_t i = 0; i < rnd_points.size(); ++i)
	{
		int intersect_count = 0;
		point_t X(rnd_points[i].x, rnd_points[i].y);
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
		if (intersect_count % 2 != 0)
			k++;
	}
	std::cout << area_calc(global_area, k, rnd_points.size()) << std::endl;
	system("pause");
	return 0;
}