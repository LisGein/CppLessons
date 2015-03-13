#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cctype>
#include <math.h>

int main()
{
	std::ifstream in("INPUT.TXT");
	std::string line;
	std::ofstream fout_("OUTPUT.TXT");
	std::vector<int> count;
	std::vector<int> first_num;
	std::vector<int> second_num;
	int num_f = 0;
	int num_s = 0;
	int summa = 0;
	int sum = 0;
	while (std::getline(in, line))
	{
		for (int i = 0; i < line.size(); ++i)
		{
			if (isdigit(line[i]))	
				if (sum <= 1)
					if (((line[i]) >= '0') && ((line[i]) <= '9'))
						first_num.push_back(line[i] - '0');
			if (isspace(line[i]))
			{
				if (second_num.size() == 0)
					if (first_num.size() > 0)
					{
						for (int i = 0; i < first_num.size(); ++i)
							second_num.push_back(first_num[i]);
						first_num.clear();
					}
				sum++;
			}
		}
	}
	for (int i = 0; i < first_num.size(); ++i)
		count.push_back(first_num[i] * pow(10, first_num.size() - 1 - i));
	for (int i = 0; i < count.size(); ++i)
		num_f += count[i];
	count.clear();

	for (int i = 0; i < second_num.size(); ++i)
		count.push_back(second_num[i] * pow(10, second_num.size() - 1 - i));
	for (int i = 0; i < count.size(); ++i)
		num_s += count[i];

	summa = num_f + num_s;
	fout_ << summa;
	fout_.close();
	return 0;
}