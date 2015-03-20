#include <fstream>
#include <iostream>
#include <set>
#include <iterator>
#include <vector>
#include <cctype>
#include <string>
#include <utility>
#include <map>

typedef std::pair<int, int> list_t;

char cipher(char &simb, int &shift)
{
	char alph;	
	int change;
	alph = (char)tolower(simb) + shift;
	while (alph > 'z')
	{
		change =  alph - 'z';
		alph = 'a' + change;
	}
	while (alph < 'a')
	{
		change = 'a' - alph;
		alph = 'z' - change;
	}
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
	std::map <int, int> errors;
	int numb_find = 0;
	std::map<int, int>::iterator it_;
	for (int shift = 0; shift < 55; ++shift)
	{
		std::ifstream check("check.txt");
		std::vector<char> count;
		std::string words;
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
		std::string check_sumb;
		for (int i = 0; i < count.size() - 3; ++i)
		{
			check_sumb += count[i];
			check_sumb += count[i + 1];
			check_sumb += count[i + 2];
			auto search_3 = comb_char.find(check_sumb);
			if (comb_char.find(check_sumb) != comb_char.end())
				numb_find++;
			check_sumb = "";
		}
		errors.insert(list_t(shift, numb_find));
		numb_find = 0;
		count.clear();
		check.close();
	}
	std::map<int, int>::iterator it;
	for (it = errors.begin(); it != errors.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	system("pause");
	return 0;
}