#include <string>
#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	std::vector <std::string> words;
	std::ifstream in("C:\\Users\\LisGein\\Documents\\Beavis and Butt Head.txt");
	std::string word;
	while (in >> word)
	{
		words.push_back(word);
	}
	std::cout << words.size() << std::endl;
	system("pause");
	return 0;
}