#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

int main()
{
	std::ifstream in("C:\\Users\\LisGein\\Documents\\Beavis and Butt Head.txt");
	std::string line;
	std::vector<int> count(27, 0);
	int x = 0;
	char z;
	int y = 0;
	while (std::getline(in, line))
	{
		for (int i = 0; i < line.size(); ++i)
		{
			if (isalpha(line[i]))
			{
				
				char current = (char)tolower(line[i]);
				y = static_cast<int>(current)- 96;
				count[y] += 1;
			}				
		}
	}
	for (int i = 0; i <= 26; ++i)
	{
		if (count[i] > 0){
			y = i + 96;
			std::cout << static_cast<char> (y) << " - " << count[i] << std::endl;
		}
		if (count[i] > x)
		{
			z = static_cast<char>(i);
			x = count[i];
		}
	}
	std::cout << "The greatest number of repetition letters: " << z << " - " << x << " times." << std::endl;
	system("pause");
	return 0;
}