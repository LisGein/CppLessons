#include <iostream>
#include <string>

class Stack
{
public:
	Stack()
		//std::string &current)
		
	{
	}

	~Stack()
	{

	}
	void push(int value)//ввод элемента массива
	{
		a = value;
	}
	void swap(Stack &other)
	{
		std::swap(a,other.a);

	}
	void peek(){

			std::cout << a << std::endl;
	}

private:
	int a;
};



int main()
{
	Stack stack;
	Stack left;
	Stack right;
	int value;
	std::cout << "enter 1" << std::endl;
		std::cin >> value;
		left.push(value);
	std::cout << "enter left.peek()" << std::endl;
	left.peek();
	std::cout << "enter peek" << std::endl;
	right.peek();
	std::cout << "swap..." << std::endl;
	right.swap(left);
	std::cout << "enter left.peek()" << std::endl;
	left.peek();
	std::cout << "enter peek" << std::endl;
	right.peek();
	std::cout << "enter 2" << std::endl;
		std::cin >> value;
		left.push(value);
		std::cout << "enter left.peek()" << std::endl;
		left.peek();
		std::cout << "enter peek" << std::endl;
		right.peek();
	std::cout << "swap 2..." << std::endl;
	std::cout << "enter left.peek()" << std::endl;
	left.peek();
	std::cout << "enter peek" << std::endl;
	right.peek();
	std::cout << "end" << std::endl;






	system("pause");
	return 0;
}