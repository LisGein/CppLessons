#include <fstream>

int main()
{
	int number;
	int res;
	std::ifstream in("INPUT.TXT");
	in >> number;
	res = (1 + number) * number / 2;
	std::ofstream out_summ("OUTPUT.TXT");
	out_summ << res;
	out_summ.close();
	return 0;
}