#pragma once

class Slice;

#include <list>
#include <string>

class Series
{
public:
	Series(const std::string& path);
	~Series();

private:
	std::list<Slice*> slices;
};

