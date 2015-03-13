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
		else if ((number >= 'A') && (number <= 'F'))
			current = number - 'A' + 10;
		else if ((number >= 'a') && (number <= 'f'))
			current = number - 'a' + 10;
		else
		{
			std::cout << "Error!";
			system("pause");
			current = 16;
		}
			
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
	int num_;
	int degree = 0;
	int otv = 0;
	std::string input_num;
	std::cout << "Enter number: " << std::endl;
	std::getline(std::cin, input_num);
	for (int i = input_num.size() - 1; i >= 0; --i)
	{
		if (iput(input_num[i]) != 16)
		{
			num_ = (iput(input_num[i]));
			otv += (conv(num_, degree));
			degree++;
		}
		else
			return 0;
	}
	std::cout << otv << std::endl;
	system("pause");
	return 0;
}