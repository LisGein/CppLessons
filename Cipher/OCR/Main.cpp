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

std::set<std::string> comb_set(std::string &line, int &shift)
{
	std::set<std::string> comb_char;
	std::string combination;
	char com;
	int amount_char = 0;
	int alphabet = 26;
	int circle;
	int alp;
	for (int i = 0; i < line.size(); ++i)
	{
		if (std::isalpha((unsigned char)line[i]))
		{
			alp = (char)tolower(line[i]) - 97;
			circle = (alp + shift) / alphabet;
			com = alp - (circle * alphabet);
			com += 97;
			combination += com;
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
	return comb_char;
};

int main()
{
	std::set<std::string> comb_char;
	std::ifstream in("input.txt");
	std::string line;
	int shift = 0;
	while (std::getline(in, line))
	{
		comb_char = comb_set(line, shift);
	}

	std::map <int, int> errors;
	int numb_find = 0;
		
	std::vector<char> count;
	std::string words;
	for (int shift = 0; shift < 26; ++shift)
	{
		std::ifstream check("check.txt");
		std::set<std::string> comb_text;
		while (std::getline(check, words))
		{
			comb_text = comb_set(words, shift);
		}
		std::set<std::string>::iterator i;
		std::string test;
		for (i = comb_text.begin(); i != comb_text.end(); ++i)		
			if (comb_char.find(*i) != comb_char.end())
				numb_find++;

		errors.insert(list_t(shift, numb_find));
		numb_find = 0;
		count.clear();		
		check.close();
	}
	
	std::map<int, int>::iterator it;
	for (it = errors.begin(); it != errors.end(); ++it)
 		std::cout << it->first << " - " << it->second << '\n';
	system("pause");
	return 0;
}