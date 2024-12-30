#include <chrono>
#include <cmath>
#include <future>
#include <iostream>
#include <thread>
#include <vector>


void workerFunction(int n)
{
    // print system id of worker thread
    std::cout << "Worker thread id = " << std::this_thread::get_id() << std::endl;

    // perform work
    for (int i = 0; i < n; ++i)
    {
        sqrt(12345.6789);
    }
}


int main() {
  // print system id of worker thread
  std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

  std::chrono::high_resolution_clock::time_point t1 =
      std::chrono::high_resolution_clock::now();

	std::vector<std::future<void>> futures;
	int nLoops = 10, nThreads = 14;
	for (int i = 0; i < nThreads; ++i) {
		futures.emplace_back(std::async(std::launch::deferred, workerFunction, nLoops));
	}

	for (const std::future<void> &ftr : futures) {
		ftr.wait();
	}


  std::chrono::high_resolution_clock::time_point t2 =
      std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	std::cout << "Execution finished after " << duration <<" microseconds" << std::endl;
}