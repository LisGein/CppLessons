#include <iostream>
#include <string>


class Node //создание класса Node
{
	friend class LinkedList;
public:
	Node()
		: next_(nullptr),
		prev_(nullptr)
	{
	}
	~Node()
	{
	}

private:
	Node * next_;  //указатель на след. элемент
	Node * prev_; // указатель на предыдущий элемент
	std::string data;	
};

class LinkedList
{
public:
	LinkedList()
		:head_(nullptr), // первый элемент
		tail_(nullptr),  //последний элемент
		capacity_(0)
	{
	}
	~LinkedList()
	{
	}
	void new_node(std::string const & data_)
	{
		Node * new_node = new Node();  // создание указателяна объект в классе Node
		new_node->data = data_; //объявление текущего элемента 
		if (head_ == nullptr) //если очередь пустая
		{
			head_ = new_node;
			tail_ = new_node;
		}
		else
		{	
			new_node->next_ = head_;
			head_->prev_ = new_node;
			head_ = new_node;
		}
	}
	void peek()
	{
		if (head_ == nullptr)
			std::cout << "Empty!\n";
		else
		{
			Node *a = head_;// идем от значения первого элемента
			std::cout << "\nAll: ";
			while (a != nullptr)
			{
				std::cout << a->data << " "; //вывод элемента находящегося по адресу head_
				a = a->next_; // присвоение адресу а значение адреса а следуещего 
			} 
		}
	}
	void pop()//удаление первого элемента
	{
		if (head_==nullptr)
		{
			std::cout << "Empty!\n";
		}
		else
		{
			head_ = head_->next_;
			std::cout << "Deleted\n";
		}
	}
private:

	Node * head_;
	Node * tail_;
	int capacity_;//число всех элементов очереди
};

int main()
{
	LinkedList list;
	std::string cmd;
	std::cout << "If you want to add element to queue, type push\n"
		<< "If you want to remove the first element, enter the pop\n"
		<< "If you want to see the first element, enter peek\n"
		<< "If you want to leave the program, type exit" << std::endl;

	while (true){
		std::cin >> cmd;
		if (cmd == "exit")
		{
			break;
		}
		if (cmd == "push")
		{
			std::string name;
			std::cout << "Enter name" << std::endl;
			std::cin >> name;
			list.new_node(name);
		}
		if (cmd == "peek")
		{
			list.peek();
		}
		if (cmd == "pop")
		{
			list.pop();
		}
	}
	return 0;
}
