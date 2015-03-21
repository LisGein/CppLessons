#include <fstream>
#include <iostream>
#include <set>
#include <iterator>
#include <vector>
#include <cctype>
#include <string>

typedef std::pair<int, int> list_t;
const int alphabet = 26;

void comb_set(std::string &line, int &shift, std::set<std::string> &text)
{
	std::string combination;
	int amount_char = 0;
	for (int i = 0; i < line.size(); ++i)
	{
		if (std::isalpha((unsigned char)line[i]))
		{
			int alp_in_numb = (char)tolower(line[i]) - 'a';
			combination += (alp_in_numb + shift) % alphabet + 'a';
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
			text.insert(combination);
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
};

int best_res(std::set<std::string> &lib, std::set<std::string> &comb_text)
{	
	int numb_find = 0;
	std::set<std::string>::iterator i;
	for (i = comb_text.begin(); i != comb_text.end(); ++i)
		if (lib.find(*i) != lib.end())
			numb_find++;	
	return numb_find;
};

void reciphers(int &shift)
{
	std::ifstream check("check.txt");
	std::string recipher;
	std::string word;
	while (std::getline(check, word))
	{
		for (int i = 0; i <= word.size(); ++i)
		{
			if (std::isalpha((unsigned char)word[i]))
			{
				int alp_in_numb = (char)tolower(word[i]) - 'a';
				recipher += (alp_in_numb + shift) % alphabet + 'a';
			}

			if (std::isspace((unsigned char)word[i]))
				recipher += ' ';
		}
	}
	std::cout << recipher << "\n";
}

int main()
{
	std::ifstream in("input.txt");
	std::string line;
	std::set<std::string> lib;	
	int shift = 0;
	while (std::getline(in, line))
		comb_set(line, shift, lib);

	std::vector<int> res;
	std::string crypted_text;
	std::string crypted_line;
	std::ifstream check("check.txt");
	while (std::getline(check, crypted_line))
	{
		crypted_text += crypted_line;
		for (int shift = 0; shift < alphabet; ++shift)
		{
			std::set<std::string> comb_text;
			comb_set(crypted_line, shift, comb_text);
			res.push_back(best_res(lib, comb_text));
		}
	}
	shift = 0;
	for (int i = 0; i < res.size(); ++i)
		if (shift < res[i])
			shift = i;
	reciphers(shift);
	system("pause");
	return 0;
}