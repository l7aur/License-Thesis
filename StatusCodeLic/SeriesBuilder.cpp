#include "SeriesBuilder.hpp"
#include "Slice.hpp"

#include <filesystem>

using namespace std::chrono_literals;

SeriesBuilder::SeriesBuilder(const std::string& path)
	: b{ getNumberOfWorkers() + 1 }
{
	size_t numberOfFiles = 0;
	for (const auto& entry : std::filesystem::directory_iterator(path)) 
		if (entry.is_regular_file())
			numberOfFiles++;

	series.resize(numberOfFiles, nullptr);
	numberOfFiles = 0;
	for (const auto& entry : std::filesystem::directory_iterator(path))
		if (entry.is_regular_file()) {
			this->submit([index = numberOfFiles, filePath = entry.path().string(), this] { this->series.at(index) = new Slice(filePath); });
			numberOfFiles++;
		}
}

SeriesBuilder::~SeriesBuilder()
{
	for (auto& slice : series)
		delete slice;
}

void SeriesBuilder::worker_thread() {
	thread_pool::worker_thread();
	b.arrive_and_wait();
}

void SeriesBuilder::waitForFinish() {
	while (!work_q.empty());
	isDone = true;
	b.arrive_and_wait();
}
