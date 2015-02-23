#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

int main()
{
	std::ifstream in("C:\\Users\\LisGein\\Documents\\Beavis and Butt Head.txt");
	std::string line;
	std::vector<int> count(256, 0);

	while (std::getline(in, line))
	{
		for (int i = 0; i < line.size(); ++i)
		{
			if (isalpha(line[i]))
			{
				char current = line[i];
				count[current] += 1;
			}				
		}
	}
	for (int i = 'a'; i <= 'z'; ++i)
	{
		std::cout << static_cast<char>(i)<< " - " << count[i] << std::endl;
	}
	system("pause");
	return 0;
}