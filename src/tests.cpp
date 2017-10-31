#include "tests.h"

namespace ip3 {
void TEST_AverageMatrix() {
	std::cout << "Testing AverageMatrix..." << std::endl;
	cv::Mat test_mat = cv::Mat::Mat(3, 3, CV_64F);

    /* 5 3 6
       2 1 9
       8 4 7 */
    test_mat.at<double>(0,0) = 5;
    test_mat.at<double>(0,1) = 3;
    test_mat.at<double>(0,2) = 6;
    test_mat.at<double>(1,0) = 2;
    test_mat.at<double>(1,1) = 1;
    test_mat.at<double>(1,2) = 9;
    test_mat.at<double>(2,0) = 8;
    test_mat.at<double>(2,1) = 4;
    test_mat.at<double>(2,2) = 7;

	std::cout << "Input: " << std::endl;
	std::cout << test_mat << std::endl;

	double average = AverageMatrix(&test_mat);
    std::cout << "TEST_AverageMatrix :: average is " << average << std::endl;

    cv::Mat test_mat2 = cv::Mat::Mat(3, 3, CV_64F);

    test_mat2.at<double>(0,0) = 3;
    test_mat2.at<double>(0,1) = 3;
    test_mat2.at<double>(0,2) = 3;
    test_mat2.at<double>(1,0) = 3;
    test_mat2.at<double>(1,1) = 3;
    test_mat2.at<double>(1,2) = 3;
    test_mat2.at<double>(2,0) = 3;
    test_mat2.at<double>(2,1) = 3;
    test_mat2.at<double>(2,2) = 3;

    std::cout << "Input: " << std::endl;
	std::cout << test_mat2 << std::endl;

    average = AverageMatrix(&test_mat2);
    std::cout << "TEST_AverageMatrix :: average is " << average << std::endl;

    test_mat.release();
}

void TEST_PadMatrix() {
	std::cout << "Testing PadMatrix..." << std::endl;

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

	std::cout << "Input:" << std::endl;
	std::cout << sobel << std::endl;
	std::cout << "Output:" << std::endl;
	std::cout << ip3::PadMatrix(&sobel) << std::endl << std::endl;

	cv::Mat random1 = cv::Mat::Mat(3, 3, CV_64F);
	random1.at<double>(0,0) = 9;
	random1.at<double>(0,1) = -25;
	random1.at<double>(0,2) = -3000;
	random1.at<double>(1,0) = 500;
	random1.at<double>(1,1) = 699;
	random1.at<double>(1,2) = 321;
	random1.at<double>(2,0) = 20;
	random1.at<double>(2,1) = 0;
	random1.at<double>(2,2) = 76;

	std::cout << "Input:" << std::endl;
	std::cout << random1 << std::endl;
	std::cout << "Output:" << std::endl;
	std::cout << ip3::PadMatrix(&random1) << std::endl;

	sobel.release();
	random1.release();
}

} // namespace
