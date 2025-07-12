#pragma once

#include <vector>
#include <string>
#include <barrier>
#include "thread_pool.hpp"

class Slice;

class SeriesBuilder : protected thread_pool
{
public:
	SeriesBuilder(const std::string& path) noexcept(false);
	~SeriesBuilder();

	void worker_thread() override;
	void waitForFinish();

private:
	std::vector<Slice*> series;
	std::barrier<> threadBarrier;
};

