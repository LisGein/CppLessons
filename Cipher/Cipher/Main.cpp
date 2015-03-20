#include <iostream>
#include <fstream>
#include <string>
#include <vector>

char cipher_(char &sim)
{
	int cipher = 3;
	char alph;

	if (isalpha(sim))
	{
		if (sim == 90)
			sim = 65;
		if (sim == 122)
			sim = 97;
		alph = sim + cipher;
	}
	else
	{
		alph = sim;
	}
	return alph;
}

int main()
{
	std::string line;
	std::vector<char> count;
	std::ifstream in("Cipher.txt");
	while (std::getline(in, line))
	{
		for (int i = 0; i < line.size(); ++i)
			count.push_back(cipher_(line[i]));
	}
	std::ofstream ciper("cip.txt");
	for (int i = 0; i < count.size(); ++i)
		ciper << count[i];
	ciper.close();
	system("pause");
	return 0;
}