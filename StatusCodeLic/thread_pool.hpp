#pragma once

#include "thread_joiner.hpp"
#include "thread_safe_queue.hpp"
#include <atomic>
#include <functional>

class thread_pool {
public:
	thread_pool() 
		: isDone{ false }, joiner{threads} {
		unsigned const threadCount = std::thread::hardware_concurrency();
		try
		{
			for (size_t i = 0; i < threadCount; ++i)
				threads.push_back(std::thread(&thread_pool::worker_thread, this));
		}
		catch (const std::exception& e)
		{
			isDone = true;
			throw;
		}
	}

	~thread_pool() {
		isDone = true;
	}

	template<typename FunctionType>
	void submit(FunctionType f) { // type erasure
		work_q.push(std::function<void()>(f));
	}

private:
	std::atomic_bool isDone;
	thread_safe_queue<std::function<void()>> work_q;
	std::vector<std::thread> threads;
	thread_joiner joiner;

	void worker_thread() {
		while (!isDone) {
			std::function<void()> task;
			if (work_q.try_pop(task)) {
				task();
			}
			else {
				std::this_thread::yield();
			}
		}
	}
};