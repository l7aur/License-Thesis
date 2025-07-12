#include "Series.hpp"
#include "Slice.hpp"

#include <filesystem>

Series::Series(const std::string& path)
{
	// override thread_pool constructor
	// for each file
	//	create a reference in the slices vector
	//	submit a worker with the location of the result and the path
	// may need a barrier in main to know when all threads finished their job
	// may need to update the Slice constructor to save the required data in a file (pipeline checkpoint)


	for (const auto& entry : std::filesystem::directory_iterator(path))
		slices.emplace_back(new Slice{});
}

Series::~Series()
{
	for (auto& slice : slices)
		delete slice;
}
