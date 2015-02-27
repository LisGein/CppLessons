#include <iostream>
#include <string>

class Node
{
	friend class FindFunc;
public:
	Node()
	{
	}
	~Node()
	{
	}
private:
	Node * next_;
	Node * prev_;
	std::string name;
	std::string n_;
};

class FindFunc
{
public:
	FindFunc()
		:head_(nullptr),
		tail_(nullptr)
	{
	}
	~FindFunc()
	{
	}
	void push(std::string const &name_)
	{
		Node * new_node = new Node();  // создание указателяна объект в классе Node
		new_node->name = name_; //объявление текущего элемента 
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
	void pop()
	{
		if (head_ == nullptr)
		{
			std::cout << "Empty!\n";
		}
		else
		{
			Node * node;
			node = head_->next_;
			delete head_;
			head_ = node;
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
				std::cout << a->name << " "; //вывод элемента находящегося по адресу head_
				a = a->next_; // присвоение адресу а значение адреса а следуещего 
			}
			std::cout << "\n";
		}
	}

	Node *find(std::string const &names)
	{
		if (head_ == nullptr)
		{
			std::cout << "Empty!\n";
		}
		else
		{
			Node * f = head_;
			while (f != nullptr)
			{
				if(f -> name == names)
				{
					return f;
				}
			   else
			   {
				   f = f->next_;
			   }
			}
			return f;
		}
	}
	void erase(Node *n)
	{
		if (head_ == tail_)
		{
			delete n;
			head_ = nullptr;
			tail_ = head_;
			return;
		}
		if (n == head_)
		{
			head_ = n->next_;
			delete n;
			head_->prev_ = nullptr;
			return;
		}
			
		if (n == tail_)
		{
			tail_ = n->prev_;
			delete n;
			tail_->next_ = nullptr;
			return;
		}
		Node * n_prev = n->prev_;
		Node * n_next = n->next_;
		delete n;
		n_next->prev_ = n_prev;
		n_prev->next_ = n_next;
	}
	void delall()
	{
		while (head_ != nullptr)
		{
			Node * node;
			node = head_->next_;
			delete head_;
			head_ = node;
		}

	}
private:
	Node * head_;
	Node * tail_;

};
int main()
{
	FindFunc func;
	std::string cmd;
	std::string propriety;
	std::cout << "If you want to add element to queue, type push\n"
		<< "If you want to remove the first element, enter the pop\n"
		<< "If you want to see the first element, enter peek\n"
		<< "If you want delete all elements, enter delete\n"
		<< "If you want delete element, enter erase\n"
		<< "If you want to leave the program, type exit"
		<< std::endl;

	while (true)
	{
		std::cin >> cmd;
		propriety = "repeat cmd";
		if (cmd == "push")
		{
			std::string name;
			std::cout << "Enter name" << std::endl;
			std::cin >> name;
			func.push(name);
			propriety = "Added";
		}
		if (cmd == "peek")
		{
			func.peek();
			propriety = "\n";
		}
		if (cmd == "pop")
		{
			func.pop();
			propriety = "Delete head_";
		}
		if (cmd == "erase")
		{
			std::string names;
			std::cout << "Enter names" << std::endl;
			std::cin >> names;
			Node *n;
			n = func.find(names);
			while (n != nullptr)
			{
				func.erase(n);
				n = func.find(names);
			}
			propriety = "Erase";

		}
		if (cmd == "exit")
		{
			break;
		}
		if (cmd == "delete")
		{
			propriety = "Delete all";
			func.delall();
		}
		std::cout << propriety << std::endl;
	}
	return 0;
}