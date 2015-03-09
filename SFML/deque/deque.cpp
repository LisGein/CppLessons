#include <iostream>
#include <deque>
#include <iterator>
struct Qwerty
{
	int qwe;
};
int main()
{
	int size = 0;
	Qwerty qwerty;
	std::deque<Qwerty> queque(size);
	int val;

	std::cout << " Enter " << std::endl;
	std::cin >> val;
	qwerty.qwe = val;
	queque.push_back(qwerty);

	for (int i = 0; i < queque.size(); i++)
	{
		std::cout << queque[i].qwe;
	}
	
	system("pause");
	return 0;
}