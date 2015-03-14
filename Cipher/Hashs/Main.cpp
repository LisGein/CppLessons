#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int pos(std::string &word_)
{
	int degree = 1;
	int code = 53;
	int code_hash;
	int test = 0;
	for (int i = 0; i < word_.size(); ++i)
	{
		if (isalnum(word_[i]))
		{
			code_hash = ((int)tolower(word_[i])) * degree;
			test += code_hash;
			std::cout << test << " - code;  ";
			degree *= code;
			std::cout << degree << " - degree;  ";
		}
	}
	std::cout <<  "\n";
	return code;
}

int main()
{
	std::fstream in("input.txt");
	std::string word;
	while (in >> word)
	{
		pos(word);
	}
	system("pause");
	return 0;
}