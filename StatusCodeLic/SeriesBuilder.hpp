#pragma once

#include <vector>
#include <string>
#include "thread_pool.hpp"

class Slice;

class SeriesBuilder : public thread_pool
{
public:
	SeriesBuilder(const std::string& path, const bool createCheckpoint) noexcept(false);
	~SeriesBuilder();

private:
	std::vector<Slice*> series;

	inline static std::string CHECKPOINT_PATH{ ".\\checkpoint\\preprocessing\\" };

	void setupSeries(const std::string& path) noexcept(false);
	void populateSeriesWithCheckpoint(const std::string& path) noexcept(false);
	void populateSeriesWithoutCheckpoint(const std::string& path) noexcept(false);

};

