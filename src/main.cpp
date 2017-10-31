#include <iostream>
#include <cstdint>
#include <cstring>

#include "matrix.h"

int main(int argc, char** argv) {
	// check args
	if (argc != 5) {
		std::cout << "\nError (main.cpp): " << std::endl;
		std::cout << "\tUSAGE: " << argv[0] << " <image path> <sigma> <T_h> <T_l>" << std::endl;
		std::cout << "\tNothing implemented yet." << std::endl;
		return -1;
	}

	// run program
	cv::Mat src_image;
	if (strcmp(argv[1], "TEST") == 0) {
		// load test data
		std::cout << "\nMessage (main.cpp): " << std::endl;
		std::cout << "Running tests..." << std::endl;
		src_image = cv::imread("../../input/lena.png", 0);
		if (src_image.data == NULL) {
			std::cout << "\nError (main.cpp): " << std::endl;
			std::cout << "\tTests failed - could not load image." << std::endl;
			return -1;
		}

		cv::Mat sobel = cv::Mat::Mat(3, 3, CV_64F);
		sobel.at<double>(0,0) = -1;
		sobel.at<double>(0,1) = 0;
		sobel.at<double>(0,2) = 1;
		sobel.at<double>(1,0) = -2;
		sobel.at<double>(1,1) = 0;
		sobel.at<double>(1,2) = 2;
		sobel.at<double>(2,0) = -1;
		sobel.at<double>(2,1) = 0;
		sobel.at<double>(2,2) = 1;

		std::cout << "Testing PadMatrix..." << std::endl;
		std::cout << sobel << std::endl;
		std::cout << ip3::PadMatrix(&sobel) << std::endl;
	} else {
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
	}

	// cleanup
	if (src_image.data != NULL) {
		src_image.release();
	}
	return 0;
}
