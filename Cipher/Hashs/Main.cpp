#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef std::pair<std::string, int> list_t;

int pos(std::string &word_, int &amount)
{
	int degree = 1;
	int code = 53;
	int code_hash;
	int test = 0;
	size_t idx;
	for (int i = 0; i < word_.size(); ++i)
		if (isalpha(word_[i]))
		{
			code_hash = ((int)tolower(word_[i])) * degree;
			test += code_hash;
			degree *= code;
		}
	idx = test % amount;
	return idx;
}

int main()
{
	std::fstream in("input.txt");
	std::string word;
	std::string word_;
	int idx;
	list_t name_age;
	int amount = 0; 
	int amount_;
	int size_hash = 10;
	int chn = 1;
	std::vector <list_t> amadeus(size_hash);
	while (in >> word)
	{
		if ((chn % 2) > 0)
		{
			idx = pos(word, size_hash);
			word_ = word;
			chn++;
		}
		else
		{		
			for (int i = 0; i < word.size(); ++i)
			{
				amount_ = pow(10, (word.size() - 1) - i);
				amount += (word[i] - '0') * (amount_);
			}
			
			if (amadeus[idx].first == word_)
			{
				amadeus[idx].second += amount;
			}
			else 
			{
				name_age = std::make_pair(word_, amount);
				amadeus[idx] = name_age;
			}			
			amount = 0;
			chn++;
		}		
	}
	for (int i = 0; i < amadeus.size(); i++)
		std::cout << amadeus[i].first << " - " << amadeus[i].second << std::endl;
	system("pause");
	return 0;
}