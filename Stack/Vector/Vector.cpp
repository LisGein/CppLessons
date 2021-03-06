#include <iostream>
#include <string>

class Stack
{
public:
	Stack()
		:head_(-1),
		capacity_(MIN_CAPACITY),
		stack_(new std::string[capacity_])      //инициализация переменных	
	{
	}

	~Stack()
	{
		delete[] stack_;  //очистка памяти
	}
	void push(std::string value)                   //ввод элемента массива
	{
		head_++;
		if (head_ == capacity_ - 1)
		{
			reserve(2 * capacity_ );
		}
		stack_[head_] = value;
	}
	void swap(Stack &other)                          //свап правого и левого массива
	{

			std::swap(stack_, other.stack_);
			std::swap(head_, other.head_);
			std::swap(capacity_, other.capacity_);
	}
	void reserve(int capacity)
	{
		std::string *stack = new std::string[capacity];
		for (int i = 0; i < capacity_; i++)
		{
			stack[i] = stack_[i]; //присваивание STACK
		}
		delete[] stack_; //удаление старого массива
		stack_ = stack;  //присваивание новому массиву скопиранного
		capacity_ = capacity;
	}
	void pop()                                        //удаление элемента массива
	{
		if (head_ == -1)
		{
			std::cout << "Cant pop, stack is null!" << std::endl;
			return;  //выходим из функции, не делая больше ничего
		}
		head_--;
	}
	void peek(){
		for (int i = 0; i < capacity_; i++)
		{
			std::cout << stack_[i] << " ";
		}
	}
	bool empty() const  //проверка на пустоту массива
	{
		return head_ == -1;
	}
private:                                             //объявление переменных
	int capacity_;
	std::string *stack_ = new std::string[capacity_];
	int head_;
	static const int MIN_CAPACITY = 2;
};
int main()
{
	Stack left;
	Stack right;
	std::string cmd;
	std::cout << "If you want to add element to queue, type push\n" 
		<< "If you want to remove the first element, enter the pop\n"
		<< "If you want to see the first element, enter peek\n"
		<< "If you want to swap arrays, enter swap\n"
		<< "If you want to leave the program, type exit" << std::endl;
	while (true)
	{
		std::cin >> cmd; //считываем с клавиатуры и сравниваем строки 
		if (cmd == "exit")
		{ 
			break; //немедленно выходим из цикла
		}
		if (cmd == "push")
		{
			std::cout << "enter the nominal value" << std::endl;
			std::string value;
			std::cin >> value; // считали 1 число
			right.push(value);
		}
		if (cmd == "pop")
		{
			right.pop();//снимаем верхнюю монету
		}
		if (cmd == "swap")
		{
			right.swap(left);
		}
		if (cmd == "peek")
		{
			right.peek();
			std::cout << " " << std::endl;
		}
	}
	return 0;
}