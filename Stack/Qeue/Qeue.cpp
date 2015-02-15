#include <iostream>
#include <string>

class Queue
{
public:
	Queue(int max_size)
		:head_(0), tail_(-1), size_(0), max_size_(max_size), queue_(new std::string[max_size_])
	{

	}
	~Queue(){
		delete[] queue_;
	}

	

	void push(std::string value){

		if (size_==max_size_) {
			std::cout << "Cant push, stack is full!" << std::endl;
			return;
		}
		else{
			if (tail_ + 1 == max_size_){
				tail_ = 0;
				size_++;
				queue_[tail_] = value;
			}
			else{
				tail_++;
				size_++;
				queue_[tail_] = value;
			}
		}

	}

	void pop(){
		

		if (head_ == tail_){
			tail_ = -1;
			head_ = 0;
			size_ = 0;
		}
		else{
			if (head_ == max_size_ - 1){
				head_ = 0;
			}
			else {
				if (size_ == 0){
					std::cout << "Cant pop, stack is null!" << std::endl;
					return;
				}
				else{
					size_--;
					head_++;
				}
			}	
		}
		
	}

	std::string peek() const {
		if (tail_ == -1){
			std::cout << "Cant peek, stack is null!" << std::endl;
		}
		else{
			std::cout << queue_[head_];
			std::cout <<" on the top of stack" << std::endl;
			return queue_[head_];

		}
	}


	bool empty() const{

	}



private:
	int size_;
	int head_;
	int tail_;
	int max_size_;
	int max_size;
	std::string value1;
	std::string *queue_ = new std::string[max_size_];
	
};


int main(){
	std::cout << "Enter the size of the array" << std::endl;
	int size;
	std::cin >> size;
	Queue queue(size);
	std::string cmd;


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
			std::string value;
			std::cin >> value;
			queue.push(value);
		
		}

		if (cmd == "pop"){
			queue.pop();
		}

		if (cmd == "peek"){
			queue.peek();
		}
		
	}
	
	return 0;
}