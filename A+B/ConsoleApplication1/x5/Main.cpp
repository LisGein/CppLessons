#include <fstream>

int main()
{
	std::fstream in("INPUT.TXT");
	int number;
	int otv;
	in >> number;
	otv = (number / 10 + 1) * number / 10 * 100 + 25;
	std::ofstream out_txt("OUTPUT.TXT");
	out_txt << otv;
	out_txt.close();	
	return 0;
}