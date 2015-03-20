#include <fstream>
#include <iostream>
#include <set>
#include <iterator>
#include <vector>
#include <cctype>
#include <string>

int main()
{
	std::set<std::string> comb_char;
	std::ifstream in("input.txt");
	std::string recombination;
	std::string line;
	std::string combination;
	int amount_char = 0;
	while (std::getline(in, line))
	{
		for (int i = 0; i < line.size(); ++i)
		{
			bool ok_comb = true;
			if (std::isalpha((unsigned char)line[i]))
			{
				combination += (char)tolower(line[i]);
				amount_char++;
			}
			if (std::isspace((unsigned char)line[i]))
			{
				combination += ' ';
				amount_char++;
			}
			if ((!isalpha((unsigned char)line[i])) && (!isspace((unsigned char)line[i])))
			{
				combination.clear();
				amount_char = 0;
			}
			if ((amount_char >= 3) && (combination.size() != 0))
			{
				comb_char.insert(combination);
				if (combination[combination.size() - 1] != ' ')
				{
					for (int i = 1; i < combination.size(); ++i)
						recombination += combination[i];
					combination.clear();
					combination += recombination;
					recombination.clear();
				}
				else 
				{
					amount_char = 1;
					combination.clear();
					combination += ' ';
				}
			}
		}
	}
	std::set<std::string>::iterator it;
 	for (it = comb_char.begin(); it != comb_char.end(); ++it)
 		std::cout <<  *it << "\n";
	
	system("pause");
	return 0;
}