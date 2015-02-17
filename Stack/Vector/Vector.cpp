#include <iostream>
#include <string>

class Stack{
public:
	Stack()
		:head_(-1),
		capacity_(MIN_CAPACITY),
		stack_(new std::string[capacity_])
	{
	}

	~Stack()
	{
		delete[] stack_;
	}
	void push(std::string value)
	{
		head_++;
		if (head_ == capacity_ - 1)
		{
			reserve(2 * capacity_ );
		}
		stack_[head_] = value;
	}

	void reserve(int capacity)
	{

		std::string *stack = new std::string[capacity];
		

		for (int i = 0; i < capacity_ ; i++)
		{
			stack[i] = stack_[i];//присваивание STACK
		}
		delete[] stack_;//удаление старого массива
	
			stack_ = stack;//присваивание новому массиву скопиранного
			capacity_ = capacity;
	}

	void pop()
	{
		if (head_ == -1)
		{
			std::cout << "Cant pop, stack is null!" << std::endl;
			return; //выходим из функции, не делая больше ничего
		}
		head_--;

	}

	

	std::string peek() const
	{
		if (head_ == -1)
		{
			std::cout << "Cant peek, stack is null!" << std::endl;
			return "";
		}

		
			return stack_[head_];
		
		
	}

	bool empty() const
	{
		return head_ == -1;
	}
private:
	int capacity_;
	std::string *stack_ = new std::string[capacity_];
	int capacity;
	std::string *stack = new std::string[capacity];
	int head_;
	static const int MIN_CAPACITY = 2;
};



int main()
{
	Stack stack;
	std::string cmd;

	std::cout << "If you want to shift the coin up, then push enter" << std::endl;
	std::cout << "If you want to remove the top coin, enter the pop" << std::endl;
	std::cout << "If you want to see the top of the coin, enter peek" << std::endl;
	std::cout << "If you want to complete the program, type exit" << std::endl;


	while (true){

		std::cin >> cmd; //считываем с клавиатуры 

		if (cmd == "exit"){ //сравниваем строки 
			break; //немедленно выходим из цикла
		}


		if (cmd == "push"){
			std::cout << "enter the nominal value" << std::endl;
			std::string value;
			std::cin >> value; // считали 1 число
			stack.push(value);
		}


		if (cmd == "pop")
		{
			stack.pop();//снимаем верхнюю монету
		}


		if (cmd == "peek")
		{
			if (!stack.empty())
			{
				std::cout << stack.peek() << " on the top of stack" << std::endl;
			}
			else
			{
				std::cout << "Queue is empty!" << std::endl;
			}
		}
	}

	return 0;
}