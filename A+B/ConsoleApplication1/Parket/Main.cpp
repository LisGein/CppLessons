#include <fstream>
#include <vector>
#include <iostream>
#include <string>

int main()
{
	std::ifstream in("input.txt");
	int neighbors = 0;
	int N, M, A, B;
	char floor;
	std::vector<char> parket;
	in >> N >> M >> A >> B;

	while (in >> floor)
		parket.push_back(floor);
	for ()
	for (int i = 0; i < parket.size(); ++i)
	{
		if (i % M == 0)
			std::cout <<"\n";
		std::cout << parket[i];
	}
	system("pause");
	return 0;
}