#include <thread>
#include <iostream>
#include <future>

void divideByNumber(std::promise<double> && prms, double num, double denom) {
	try {
		if (denom == 0) {
			throw std::runtime_error("Exception from thread: Division by zero");
		} else {
			prms.set_value(num / denom);
		}
	} catch (...) {
		prms.set_exception(std::current_exception());
	}
}

int main() {
	std::promise<double> prms;
	std::future<double> ftr = prms.get_future();

	double num = 42.0, denom = 1.0;
	std::thread t(divideByNumber, std::move(prms), num, denom);

	try {
		double result = ftr.get();
		std::cout << "Result: " << result << std::endl;
	} catch (std::runtime_error e) {
		std::cout << e.what() << std::endl;
	}

	t.join();

	return 0;
}