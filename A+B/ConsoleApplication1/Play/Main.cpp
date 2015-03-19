#include <iostream>
#include <fstream>


int main()
{
	std::fstream in("INPUT.TXT");
	int number;
	int otv;
	in >> number;
	otv = number * 100 + 90 + (9 - number);
	std::ofstream otv_("OUTPUT.TXT");
	otv_ << otv;
	return 0;
}