#include <iostream>
#include <string>

class Queue
{
public:
	Queue()
		:head_(-1), tail_(-1)
	{

	}
	~Queue(){

	}

	void firstpush(int MAX_SIZ){
		MAX_SIZE = MAX_SIZ;
		std::cout << "Your stack is empty, so enter the first element of the arrayenter" << std::endl;
		int  felement;
		std::cin >> felement;
		head_++;
		tail_++;
		queue_[tail_] = felement;
	}

	void push(int value){
		if (tail_ == MAX_SIZE - 1){
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
		head_++;
	}

	int peek() const {
		std::cout << queue_[head_] << std::endl;
		return queue_[head_];
	}

	void del() {
		delete [] queue_;

	}

	bool empty() const{

	}



private:
	int head_;
	int tail_;
	int MAX_SIZE;
	int *queue_ = new int[MAX_SIZE];
};


int main(){

	Queue queue;
	std::string cmd;

	/*std::cout << "Enter the size of the array" << std::endl;
	int MAX_SIZE;
	std::cin >> MAX_SIZE;
	queue.MAX_SIZE;
	std::cout << "Your stack is empty, so enter the first element of the arrayenter" << std::endl;
	int felement;
	std::cin >> felement;*/
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
	queue.del();
	return 0;
}