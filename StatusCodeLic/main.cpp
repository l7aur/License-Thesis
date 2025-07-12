#include <iostream>

#include "SeriesBuilder.hpp"

int main() {

	/*
	PREPROCESSING to do: checkpoint
	PROCESSING 1: canny edge detection
	PROCESSING 2: generate points
	PROCESSING 3: generate mesh
	*/

	SeriesBuilder mySeries{"C:\\Users\\L7aur\\Desktop\\StatusCodeLic\\dicom_data\\Series 002 [CT - Crane SPC]"};

	mySeries.waitForFinish();
	std::cout << "---EOE---\n";
	std::cin.get();
	return EXIT_SUCCESS;
}