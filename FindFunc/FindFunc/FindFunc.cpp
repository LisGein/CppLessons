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
			std::cout << "Deleted\n";
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
		}
	}

	Node find(std::string const &names)
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
					break;
				}
			   else
			   {
				   f = f->next_;
			   }
			}
			return f;
			std::cout << f << " -f/n";
		}
	}
	void erase(Node *n)
	{
		Node * next_node;
		next_node = n->next_;
		Node * prev_node;
		prev_node = n->prev_;
		delete n;
		n = next_node;
		n = prev_node;
		std::cout << "Deleted\n";

	}
private:
	Node * head_;
	Node * tail_;

};
int main()
{
	FindFunc func;
	std::string cmd;
	std::cout << "Enter cmd" << std::endl;
	while (true)
	{
		std::cin >> cmd;
		if (cmd == "push")
		{
			std::string name;
			std::cout << "Enter name" << std::endl;
			std::cin >> name;
			func.push(name);
		}
		if (cmd == "delete")
		{
			std::string name;
			std::cout << "Enter name" << std::endl;
			std::cin >> name;
		}
		if (cmd == "peek")
		{
			func.peek();
		}
		if (cmd == "pop")
		{
			func.pop();
		}
		if (cmd == "erase")
		{

			std::string names;
			std::cout << "Enter names" << std::endl;
			std::cin >> names;
			func.find(names);
			Node *n = func.find(names);
			if (n != nullptr)
				func.erase(n);

		}
		if (cmd == "exit")
		{
			break;
		}

	}
	return 0;
}