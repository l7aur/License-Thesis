#pragma once

#include <vector>
#include <string>
#include <barrier>
#include "thread_pool.hpp"

class Slice;
using Series = std::vector<Slice*>;

class SeriesBuilder : protected thread_pool
{
public:
	SeriesBuilder(const std::string& path);
	~SeriesBuilder();

	void worker_thread() override;
	void waitForFinish();

private:
	Series series;
	std::barrier<> b;
};

