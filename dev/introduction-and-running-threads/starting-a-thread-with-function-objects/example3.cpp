#include <iostream>
#include <thread>

class Vehicle {
 private:
  int _id;

 public:
	Vehicle(int id) : _id(id) {}
  void operator()() {
    std::cout << "Vehicle #" << _id << " has been created \n";
  }
};

int main() {

  std::thread t = std::thread(Vehicle(1));  // Use copy initialization

  // do something in main()
  std::cout << "Finished work in main \n";

  // wait for thread to finish
  t.join();

  return 0;
}