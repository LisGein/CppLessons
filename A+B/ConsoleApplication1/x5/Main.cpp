#include <fstream>
#include <math.h>

int main()
{
	std::ifstream in("INPUT.TXT");
	int number;
	int first_num;
	int second_num;
	int otv;
	in >> number;
	first_num = number / 10;
	second_num = first_num + 1;
	otv = (first_num * second_num * 100) + 25;
	std::ofstream out_txt("OUTPUT.TXT");
	out_txt << otv;
	out_txt.close();
	
	return 0;
}