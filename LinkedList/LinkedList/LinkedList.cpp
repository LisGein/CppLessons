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
		capacity_(1)
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
			capacity_++;
			/*new_node->next_ = new_node; // то функции next_ объекта push_front(push_front.next_) присваивается значение текущего элемента
			tail_ = new_node; // последним элементом назначается текущий элемент
			head_ = new_node; //и первым элементом назначается текущий элемент
			capacity_++;*/
		}
		else
		{
			//for (capacity_; capacity_>1; capacity_--)
				//head_ = head_->prev_;
			new_node->next_ = head_;
			head_->next_->prev_ = new_node;
			head_ = new_node;
			head_->prev_ = nullptr;
			capacity_++;
			
			/*
			Node *p = head_; // присвоение указателю на объект p адрес первой переменной

			for (capacity_; capacity_>1; capacity_--)
				p = p->prev_;//присвоение каждой p предыдущий p
			p->next_->prev_ = new_node; //присваивание текущего элемента очереди как значение предыдущего для следующего #извините(с)
			new_node->next_ = head_->next_; //вот тут вот...
			new_node->prev_ = p; //... я запутылась
			p->next_ = new_node; // указателю на следующий объект присваивается указатель на текущий объект
			head_ = new_node; //первым элементом назначается текущий элемент		
			capacity_++;
			// в целом всё это выглядит отвратно...*/
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
			list.new_node(name);

		}
		if (cmd == "peek")
		{
			list.peek();
		}
	}
	return 0;
}
