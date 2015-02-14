#include <iostream>
#include <string>

class Queue
{
public:
	Queue()
		:head_(0), tail_(-1), max_size_(max_size), queue_(new int[max_size_])
	{

	}
	~Queue(){
		delete[] queue_;
	}

	void firstpush(int max_size){
		max_size_ = max_size;
		
	}

	void push(int value){
		if (tail_ == max_size_ - 1){
			std::cout << "Cant push, stack is full!" << std::endl;
			return;
		}
		else{

				tail_++;
				queue_[tail_] = value;
			}
	}

	void pop(){
		if (head_ == -1){
			std::cout << "Cant pop, stack is null!" << std::endl;
			return;
		}
		else{
			head_++;
		}
	}

	int peek() const {
		std::cout << queue_[head_] << std::endl;
		return queue_[head_];
	}


	bool empty() const{

	}



private:
	int head_;
	int tail_;
	int max_size_;
	int max_size;
	int *queue_ = new int[max_size_];
};


int main(){

	Queue queue;
	std::string cmd;

	std::cout << "Enter the size of the array" << std::endl;
	int MAX_SIZ;
	std::cin >> MAX_SIZ;
	queue.firstpush(MAX_SIZ);

	std::cout << "If you want to shift the coin up, then push enter" << std::endl;
	std::cout << "If you want to remove the top coin, enter the pop" << std::endl;
	std::cout << "If you want to see the top of the coin, enter peek" << std::endl;
	std::cout << "If you want to complete the program, type exit" << std::endl;

	while (true){
		std::cin >> cmd;

		if (cmd == "exit"){
			break;
		}

		if (cmd == "push"){
			std::cout << "Enter the nominal value" << std::endl;
			int value;
			std::cin >> value;
			queue.push(value);
		
		}

		if (cmd == "pop"){
			queue.pop();
		}

		if (cmd == "peek"){
			std::cout << queue.peek() << " on the top of stack" << std::endl;
		}
		
	}
	
	return 0;
}