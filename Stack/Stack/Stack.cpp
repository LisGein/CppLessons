// Stask.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cassert>

class Stack{
public:
	Stack()
		:head_(-1)
	{
	}
	
	~Stack(){
	}
	void push()
	{
		head_++;
		stack_[head_] = value;
	}

	void pop()
	{
		head_--;
	}

	int peek() const
	{

		std::cout << stack_[head_] << std::endl;
		return stack_[head_]; //внутри методов к полям(переменным класса) можно обращаться просто по имени.
	}

	bool empty() const
	{
	}
private:
	static const int MAX_SIZE = 10;
	int stack_[MAX_SIZE];
	int head_;
};

int _tmain(int argc, _TCHAR* argv[])
{
	Stack stack;
	std::string cmd;

	std::cout << "If you want to shift the coin up, then push enter" << std::endl;
	std::cout << "If you want to remove the top coin, enter the pop" << std::endl;
	std::cout << "If you want to see the top of the coin, enter peek" << std::endl;
	std::cout << "If you want to complete the program, type exit" << std::endl;

	std::cin >> cmd; //считываем с клавиатуры 
	while (true) //бесконечный цикл
	{
	if (cmd == "exit"){ //сравниваем строки 
		break; //немедленно выходим из цикла
	}
	if (cmd == "push")
	{
		std::cout << "enter the nominal value" << std::endl;
		int value;
		std::cin >> value; // считали 1 число
		stack.push(value);
		//тут надо реализовать push для монеты с номиналом value
	}

	if (cmd == "pop")
	{
		stack.pop();//снимаем верхнюю монету
	}

	if (cmd == "peek")
	{
		std::cout << stack.peek() << " on the top of stack" << std::endl;
		//печатаем номинал монеты, которая лежит наверху.
	}
}
return 0;
}
	
