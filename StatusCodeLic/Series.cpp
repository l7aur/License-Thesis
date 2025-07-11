#include "Series.hpp"
#include "Slice.hpp"

#include <filesystem>

Series::Series(const std::string& path)
{
	// to do multithreading
	for (const auto& entry : std::filesystem::directory_iterator(path))
		slices.emplace_back(new Slice{ entry.path().string() });
}

Series::~Series()
{
	for (auto& slice : slices)
		delete slice;
}
