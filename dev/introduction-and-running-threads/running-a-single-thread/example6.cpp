#include <iostream>
#include <thread>

void threadFunction()	{
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	std::cout << "Finished work in thread\n";
}

int main() {
	std::thread t(threadFunction);
	
	t.detach();

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	std::cout << "Finished work in main\n";
}