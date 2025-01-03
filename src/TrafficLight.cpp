#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */

template <typename T>
T MessageQueue<T>::receive()
{
    // Create a unique lock for the mutex
    std::unique_lock<std::mutex> uLock(_mutex);
    
    // Wait for new messages in the queue
    // Lambda function checks if queue is not empty
    _condition.wait(uLock, [this] { return !_queue.empty(); });

    // Move the first message from queue
    T msg = std::move(_queue.front());
    _queue.pop_front();

    return msg;
}


template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    // create a lock to visit queue safely
    std::lock_guard<std::mutex> lock(_mutex);
    
    // move message to queue
    _queue.push_back(std::move(msg));
    
    // notify a waiting thread
    _condition.notify_one();
}

/* Implementation of class "TrafficLight" */

TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

TrafficLight::~TrafficLight()
{
    // No specific cleanup needed
}

void TrafficLight::waitForGreen()
{
    // Loop until green light is received
    while (true)
    {
        // Get current phase from message queue
        TrafficLightPhase currentPhase = _messageQueue.receive();
        
        // Check if received phase is green
        if (currentPhase == TrafficLightPhase::green)
        {
            return;
        }
    }
}


TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class.
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // initial random generator
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(4000, 6000); // 4-6seconds，and convert to milliseconds

    // init stop watch
    auto lastUpdate = std::chrono::system_clock::now();
    
    // generate first cycle duration time(ms)
    long cycleDuration = distr(eng);

    while (true)
    {
        // reduce cpu burden
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // compute updated time for previous
        long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - lastUpdate
        ).count();

        // Check if need to shift traffic light signal
        if (timeSinceLastUpdate >= cycleDuration)
        {
            // shift phase
            _currentPhase = (_currentPhase == TrafficLightPhase::red) ? 
                            TrafficLightPhase::green : 
                            TrafficLightPhase::red;

            // Using move semantic to send signal to message queue
            _messageQueue.send(std::move(_currentPhase));

            // generate new random duration time
            cycleDuration = distr(eng);

            // reset stop watch
            lastUpdate = std::chrono::system_clock::now();
        }
    }
}