#include <fstream>
#include <iostream>
#include <set>
#include <iterator>
#include <vector>
#include <cctype>
#include <string>

char cipher(char &simb, int &shift)
{
	char alph;	
		//if ((simb <= 'A')||(simb >= 'Z'))
			simb = simb + 32;
		alph = simb;
		//+shift;
	return alph;
};

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
					combination = combination.substr(1);
				else 
				{
					amount_char = 1;
					combination.clear();
					combination += ' ';
				}
			}
		}
	}
	std::ifstream check("check.txt");
	std::string words;
	int shift =  3 ;
	std::vector<char> count;
	while (std::getline(check, words))
	{
		for (int i = 0; i < words.size(); ++i)
		{
			if (std::isalpha((unsigned char)words[i]))	
				count.push_back(cipher(words[i], shift));

			if (std::isspace((unsigned char)words[i]))
				count.push_back(' ');
		}
	}
	for (int i = 0; i < count.size(); ++i)
		std::cout << count[i];
	system("pause");
	return 0;
}