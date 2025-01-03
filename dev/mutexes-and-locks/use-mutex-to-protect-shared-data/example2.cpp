#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex> // step1
#include<algorithm>

class Vehicle
{
public:
    Vehicle(int id) : _id(id) {}

private:
    int _id;
};

class WaitingVehicles
{
public:
    WaitingVehicles() {}

    // getters / setters
    void printSize()
    {
        _mutex.lock(); // step3
        std::cout << "#vehicles = " << _vehicles.size() << std::endl;
        _mutex.unlock(); // step3
    }

    // typical behaviour methods
    void pushBack(Vehicle &&v)
    {
        _mutex.lock(); // step3
        _vehicles.emplace_back(std::move(v)); // data race would cause an exception
        _mutex.unlock(); // step3
    }

private:
    std::vector<Vehicle> _vehicles; // list of all vehicles waiting to enter this intersection
    std::mutex _mutex; // step2
};

int main()
{
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles); 
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 1000; ++i)
    {
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
    }

    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
        ftr.wait();
    });

    queue->printSize();

    return 0;
}
