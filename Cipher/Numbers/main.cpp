#include <iostream>
#include <string>
#include <vector>

char iput(char &number)
{
	int current;
	if (isalnum(number))
	{		
		if ((number > 47) && (number < 58))
			current = number - 48;
		if ((number >= 'A') && (number <= 'F'))
			current = number - 'A' + 10;
		if ((number >= 'a') && (number <= 'f'))
			current = number - 'a' + 10;
		else
			current = 0;
		return current;
	}
}
int conv(int &numb, int degree_)
{
	int numbs = numb*pow(16, degree_);
	return numbs;
}
int main()
{
	int numbs;
	int degree = -1;
	int otv = 0;
	std::string input_num;
	std::cout << "Enter number: " << std::endl;
	std::getline(std::cin, input_num);
	std::vector<int> o_nums;
	for (int i = 0; i < input_num.size(); ++i)
		if (iput(input_num[i]) != 0)
		{
			o_nums.push_back(iput(input_num[i]));
			degree += o_nums.size();
		}
		else
		{
			std::cout << "Error!";
			system("pause");
			return 0;
		}
	for (int i = 0; i < o_nums.size(); ++i)
	{
		otv += (conv(o_nums[i], degree));
		degree--;
	}
	std::cout << otv;
	system("pause");
	return 0;
}