#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

int main()
{
	std::ifstream in("C:\\Users\\LisGein\\Documents\\Beavis and Butt Head.txt");
	std::string line;
	std::vector<int> count(26, 0);
	int summ = 0;
	int MaxTimes = 0;
	int NameAlpha = 0;
	char MaxName;
	while (std::getline(in, line))
	{
		for (int i = 0; i < line.size(); ++i)
		{
			if (isalpha(line[i]))
			{
				summ += 1;
				char current = (char)tolower(line[i]);
				count[current-'a'] += 1;
			}				
		}
	}
	if ( summ > 0)
	{
		for (int i = 0; i < count.size(); ++i)
		{
			if (count[i] > 0){
				NameAlpha = i + 'a';
				std::cout << static_cast<char> (NameAlpha) << " - " << count[i] << std::endl;
			}
			if (count[i] > MaxTimes)
			{
				MaxName = static_cast<char>(i);
				MaxTimes = count[i];
			}
		}
		std::cout << "The greatest number of repetition letters: " << MaxName << " - " << MaxTimes << " times." << std::endl;
	}
	else
	{
		std::cout << "File is empty!" << std::endl;
	}
	system("pause");
	return 0;
}