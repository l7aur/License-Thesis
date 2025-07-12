#pragma once

#include <thread>
#include <vector>

class thread_joiner {
public:
	explicit thread_joiner(std::vector<std::thread>& threads_) :
		threads{ threads_ }
	{ }

	~thread_joiner() {
		for (size_t i = 0; i < threads.size(); ++i)
			if (threads.at(i).joinable())
				threads.at(i).join();
	}

private:
	std::vector<std::thread>& threads;
};