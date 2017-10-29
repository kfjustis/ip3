#include <iostream>
#include <cstdint>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

int main(int argc, char** argv) {
	// check args
	if (argc != 5) {
		std::cout << "\nError (main.cpp): " << std::endl;
		std::cout << "\tUSAGE: " << argv[0] << " <image path> <sigma> <T_h> <T_l>" << std::endl;
		std::cout << "\tNothing implemented yet." << std::endl;
		return -1;
	}

	// load input data
	cv::Mat src_image;
	src_image = cv::imread(argv[1], 0);
	if (src_image.data == NULL) {
		std::cout << "\nError (main.cpp): " << std::endl;
		std::cout << "Failed to load source image -->" << std::endl;
		std::cout << "\tMake sure passed file was an image with correct path" << std::endl;
		return -1;
	}

	uint8_t sigma = (uint8_t) atoi(argv[2]);
	uint8_t t_h = (uint8_t) atoi(argv[3]);
	uint8_t t_l = (uint8_t) atoi(argv[4]);

	std::cout << "\nMessage (main.cpp): " << std::endl;
	std::cout << "Running canny edge detector on:" << std::endl;
	std::cout << "\tImage: " << argv[1] << std::endl;
	std::cout << "\tSigma: " << (int) sigma << std::endl;
	std::cout << "\tHigh threshold: " << (int) t_h << std::endl;
	std::cout << "\tLow threshold: " << (int) t_l << std::endl;

	// cleanup
	src_image.release();
	return 0;
}
