#include <iostream>
#include <string>

class Stack
{
public:
	Stack()
		:head_(0),
		capacity_(3)
	{
	}

	~Stack()
	{
		
	}
	void push(std::string value)//ввод элемента массива
	{
		head_++;
		stack_[head_] = value;
	}
	void swap(Stack &other)
	{
		std::swap(head_, other.head_);
	}
	void peek(){
		for (int i = 0; i < capacity_; i++)
		{
			std::cout << stack_[i] << std::endl;
		}
	}
	
private:
	int head_;
	int capacity_;
	std::string *stack_ = new std::string[capacity_];
};



int main()
{
	Stack stack;
	Stack left;
	Stack right;
	Stack &current = left;
	std::string value;
	std::cout << "1" << std::endl;
	for (int i = 0; i < 3; i++){
		std::cin >> value;
		stack.push(value);
	}
	stack.peek();
	std::cout << "swap:" << std::endl;
	right.swap(left);
	std::cout << "2" << std::endl;
	stack.peek();
	for (int i = 0; i < 3; i++){
		std::cin >> value;
		stack.push(value);
	}
	std::cout << "3" << std::endl;
	stack.peek();


	
	
	
	system("pause"); 
	return 0;
}