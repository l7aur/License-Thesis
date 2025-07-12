#pragma once

#include "thread_joiner.hpp"
#include "thread_safe_queue.hpp"
#include "Warnings.hpp"
#include <atomic>
#include <functional>

class thread_pool {
public:
	thread_pool() noexcept(false)
		: isDone{ false }, joiner{ threads } {
		unsigned const threadCount = std::thread::hardware_concurrency() / 2;
		try {
			for (size_t i = 0; i < threadCount; ++i)
				threads.push_back(std::thread(&thread_pool::worker_thread, this));
		}
		catch (const std::exception& e) {
			isDone = true;
			throw e;
		}
	}

	~thread_pool() {
		isDone = true;
	}

	template<typename FunctionType>
	void submit(FunctionType f) { // type erasure
		work_q.push(std::function<void()>(f));
	}

	MUST_USE_VALUE_ATTR const int getNumberOfWorkers() const { return static_cast<int>(threads.size()); }

protected:
	std::atomic_bool isDone;
	thread_safe_queue<std::function<void()>> work_q;

	virtual void worker_thread() {
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

private:
	std::vector<std::thread> threads;
	thread_joiner joiner;
};