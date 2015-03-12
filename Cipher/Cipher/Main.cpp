#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
	int cipher = 3;
	char alph;
	std::string line;
	std::vector<char> count;
	std::fstream in("Cipher.txt");
	while (std::getline(in, line))
	{
		for (int i = 0; i < line.size(); ++i)
			if (isalpha(line[i]))
			{
				alph = line[i];
				count.push_back(alph + cipher);
			}
			else
			{
				alph = line[i];
				count.push_back(alph);
			}
	}
	for (int i = 0; i < count.size(); ++i)
		std::cout << count[i];

	system("pause");
	return 0;
}