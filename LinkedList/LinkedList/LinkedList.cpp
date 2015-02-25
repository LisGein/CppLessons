#include <iostream>
#include <string>


class Node //создание класса Node
{
	friend class LinkedList;
public:
	Node()
	{
	}
	~Node()
	{
	}
	Node * next_;  //указатель на след. элемент
	Node * prev_; // указатель на предыдущий элемент
private:
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
	void push_front(std::string const & data_)
	{
		Node * push_front = new Node();  // создание указателяна объект в классе Node
		push_front->data = data_; //объявление текущего элемента 
		if (head_ == NULL) //если очередь пустая
		{
			push_front->next_ = push_front; // то функции next_ объекта push_front(push_front.next_) присваивается значение текущего элемента
			tail_ = push_front; // последним элементом назначается текущий элемент
			head_ = push_front; //и первым элементом назначается текущий элемент
			capacity_++;
		}
		else
		{
			Node *p = head_; // присвоение указателю на объект p адрес первой переменной

			for (capacity_; capacity_>1; capacity_--)
				p = p->prev_;//присвоение каждой p предыдущий p
			p->next_->prev_ = push_front; //присваивание текущего элемента очереди как значение предыдущего для следующего #извините(с)
			push_front->next_ = p->next_; //вот тут вот...
			push_front->prev_ = p; //... я запутылась
			p->next_ = push_front; // указателю на следующий объект присваивается указатель на текущий объект
			head_ = push_front; //первым элементом назначается текущий элемент		
			capacity_++;
			// в целом всё это выглядит отвратно...
		}
	}
	void peek()
	{
		if (head_ == NULL) 
			std::cout << "Empty!\n";
		else
		{
			Node *a = head_;// идем от значения первого элемента
			std::cout << "\nAll: ";
			do
			{
				std::cout << a->data << " "; //вывод элемента находящегося по адресу head_
				a = a->next_; // присвоение адресу а значение адреса а следуещего 
			} 
			while (a != tail_); // до последнего
			std::cout << a->data << " " << std::endl;//
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
			list.push_front(name);

		}
		if (cmd == "peek")
		{
			list.peek();
		}
	}
	return 0;
}
