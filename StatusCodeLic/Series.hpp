#pragma once

class Slice;

#include <vector>
#include <string>
#include "thread_pool.hpp"

class Series : private thread_pool<Slice*>
{
public:
	Series(const std::string& path);
	~Series();

private:
	std::vector<Slice*> slices;
};

