#include <iostream>
#include <string>

class Queue
{
public:
	Queue(int max_size)
		:head_(0),
		tail_(-1),
		size_(0),
		max_size_(max_size),
		queue_(new std::string[max_size_])
		//инициализация переменных
	{
	}

	~Queue()
	{
		delete[] queue_;
	}

	void push(std::string value)//добавление элементов в массив
	{

		if (size_ == max_size_) 
		{
			std::cout << "Cant push, queue is full!" << std::endl;
			return;
		}
		else
		{
			if (tail_ + 1 == max_size_)
			{
				tail_ = 0;
			}
			else
			{
				tail_++;
			}
			size_++;
			queue_[tail_] = value;
		}

	}

	void pop() //удаление первого элемента из массива 
	{
		if (head_ == tail_) //если в массиве остался последний элемент, то "обнуляем переменные"
		{ 
			tail_ = -1;
			head_ = 0;
			size_ = 0;
		}
		else // иначе:
		{                
			if (head_ == max_size_ - 1)//если head_ последний элемент массива то обнуляем его и уменьшаем раззмер данных оставшихся в массиве
			{ 
				head_ = 0;
				size_--;
			}
			
			if (size_ == 0) //если количество данных в массиве равно нулю, то массив пуст и выводим сообщение об этом
				{
					std::cout << "Cant pop, queue is null!" << std::endl;
					return;
				}
				else//если head_ не последний элемент массива и размер массива больше 0, то удаляем первый элемент массива
				{
					size_--;
					head_++;
				}
		}
		
	}

	std::string peek() const // вывод первого элемента очереди
	{
		if (size_ == 0)
		{
			std::cout << "Cant peek, stack is null!" << std::endl;
			return "";
		}
	
			return queue_[head_];
	}

	bool empty() const // проверка на пустоту массива
	{
		return size_ == 0;
	}

private:
	//объявление переменных
	int size_;
	int head_;
	int tail_;
	int max_size_;
	std::string *queue_ = new std::string[max_size_];
	
};

int main()
{
	std::cout << "Enter the size of the array" << std::endl;
	int size;
	while (!(std::cin >> size))//проверка на правильность ввода массива
	{
		std::cin.clear(); //после ошибки поток "сломан". Говорим ему что все на самом деле ОК
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Пропускаем все символы которые остались в потоке.
		std::cout << "You have entered the wrong array size!" << std::endl;
	}

		Queue queue(size);

		std::string cmd;

		std::cout << "If you want to add element to queue, type push\n" //так тоже можно делать перевод строки
			<< "If you want to remove the first element, enter the pop\n"//но std::endl делает еще std::cout.flush(), до вызова флаша текст может оставаться в буфере и не выводиться на экран.
			<< "If you want to see the first element, enter peek\n"
			<< "If you want to leave the program, type exit" << std::endl;
		
		while (true)
		{
			std::cin >> cmd;

			if (cmd == "exit")
			{
				break;
			}

			if (cmd == "push")
			{
				std::cout << "Enter the nominal value" << std::endl;
				std::string value;
				std::cin >> value;
				queue.push(value);

			}

			if (cmd == "pop")
			{
				queue.pop();
			}

			if (cmd == "peek")
			{
				if (!queue.empty())
				{
					std::cout << queue.peek() << " on the top of stack" << std::endl;
				}
				else
				{
					std::cout << "Queue is empty!" << std::endl;
				}
			}
		}
	
	
	return 0;
}