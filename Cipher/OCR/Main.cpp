#include <fstream>
#include <iostream>
#include <set>
#include <iterator>
#include <vector>
#include <cctype>
#include <string>

int main()
{
	std::ifstream in("input.txt");
	char character;
	std::string test;
	std::string combination;
	int amount_char = 0;
	std::set<std::string> comb_char;
	std::set<std::string>::iterator it;
	while (std::getline(in, test))
	{
		for (int i = 0; i < test.size(); ++i)
		{
			if (std::isalpha(test[i]))
			{
				combination += (char)tolower(test[i]);
				amount_char++;
			}
			if (std::isspace(test[i]))
			{
				combination += ' ';
				amount_char++;
			}
			if (amount_char % 3 == 0)
			{
				comb_char.insert(combination);
				combination.clear();
			}
		}
	}
	for (it = comb_char.begin(); it != comb_char.end(); ++it)
		std::cout <<  *it << "\n";
	std::cout << combination;
	system("pause");
	return 0;
}