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

	double average = ip3::AverageMatrix(&test_mat);
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

    average = ip3::AverageMatrix(&test_mat2);
    std::cout << "TEST_AverageMatrix :: average is " << average << std::endl;

    test_mat.release();
	test_mat2.release();
}

void TEST_ConvolveImage() {
	return;
}

void TEST_ConvolveMatrix() {
	std::cout << "Testing ConvolveMatrix..." << std::endl;
	cv::Mat tm = cv::Mat::Mat(3, 3, CV_64F);
    /* 40 42 46
       46 50 55
       52 56 58 */
    tm.at<double>(0,0) = 40;
    tm.at<double>(0,1) = 42;
    tm.at<double>(0,2) = 46;
    tm.at<double>(1,0) = 46;
    tm.at<double>(1,1) = 50;
    tm.at<double>(1,2) = 55;
    tm.at<double>(2,0) = 52;
    tm.at<double>(2,1) = 56;
    tm.at<double>(2,2) = 58;

	cv::Mat k = cv::Mat::Mat(3, 3, CV_64F);
    /* 0 1 0
       0 0 0
       0 0 0 */
    k.at<double>(0,0) = 0;
    k.at<double>(0,1) = 1;
    k.at<double>(0,2) = 0;
    k.at<double>(1,0) = 0;
    k.at<double>(1,1) = 0;
    k.at<double>(1,2) = 0;
    k.at<double>(2,0) = 0;
    k.at<double>(2,1) = 0;
    k.at<double>(2,2) = 0;

	std::cout << "Input slice: " << std::endl;
	std::cout << tm << std::endl;
	std::cout << "Input kernel: " << std::endl;
	std::cout << k << std::endl;

	int value = ip3::ConvolveMatrix(&tm, &k);

	std::cout << "Calculated value: " << std::endl;
	std::cout << value << std::endl;

	cv::Mat tm2 = cv::Mat::Mat(3, 3, CV_64F);
    /* 40 42 46
       46 50 55
       52 56 58 */
    tm2.at<double>(0,0) = 1;
    tm2.at<double>(0,1) = 2;
    tm2.at<double>(0,2) = 3;
    tm2.at<double>(1,0) = 4;
    tm2.at<double>(1,1) = 5;
    tm2.at<double>(1,2) = 5;
    tm2.at<double>(2,0) = 7;
    tm2.at<double>(2,1) = 8;
    tm2.at<double>(2,2) = 9;

	cv::Mat k2 = cv::Mat::Mat(3, 3, CV_64F);
    /* 0 1 0
       0 0 0
       0 0 0 */
    k2.at<double>(0,0) = 1;
    k2.at<double>(0,1) = 2;
    k2.at<double>(0,2) = 1;
    k2.at<double>(1,0) = 0;
    k2.at<double>(1,1) = 0;
    k2.at<double>(1,2) = 0;
    k2.at<double>(2,0) = -1;
    k2.at<double>(2,1) = -2;
    k2.at<double>(2,2) = -1;

	std::cout << "Input slice 2: " << std::endl;
	std::cout << tm2 << std::endl;
	std::cout << "Input kernel 2: " << std::endl;
	std::cout << k2 << std::endl;

	value = ip3::ConvolveMatrix(&tm2, &k2);

	std::cout << "Calculated value 2: " << std::endl;
	std::cout << value << std::endl;

	tm.release();
	tm2.release();
	k.release();
	k2.release();
}

void TEST_GetMatrixSlice() {
	std::cout << "Testing GetMatrixSlice..." << std::endl;

	cv::Mat test = cv::Mat::Mat(3, 3, CV_64F);
	/* 1 2 3
       4 5 6
       7 8 9 */
    test.at<double>(0,0) = 1;
    test.at<double>(0,1) = 2;
    test.at<double>(0,2) = 3;
    test.at<double>(1,0) = 4;
    test.at<double>(1,1) = 5;
    test.at<double>(1,2) = 6;
    test.at<double>(2,0) = 7;
    test.at<double>(2,1) = 8;
    test.at<double>(2,2) = 9;

	std::cout << "Input: " << std::endl;
	std::cout << test << std::endl;

	cv::Mat slice1 = ip3::GetMatrixSlice(&test,0,0,3);
	std::cout << "Full slice: " << std::endl;
	std::cout << slice1 << std::endl;

	cv::Mat test_p = ip3::PadMatrix(&test);
	std::cout << "Input padded: " << std::endl;
	std::cout << test_p << std::endl;

	cv::Mat slice2 = ip3::GetMatrixSlice(&test_p,0,0,3);
	std::cout << "TL slice: " << std::endl;
	std::cout << slice2 << std::endl;

	cv::Mat slice3 = ip3::GetMatrixSlice(&test_p,0,2,3);
	std::cout << "TR slice: " << std::endl;
	std::cout << slice3 << std::endl;

	slice3 = ip3::GetMatrixSlice(&test_p,2,0,3);
	std::cout << "BL slice: " << std::endl;
	std::cout << slice3 << std::endl;

	slice3 = ip3::GetMatrixSlice(&test_p,2,2,3);
	std::cout << "BR slice: " << std::endl;
	std::cout << slice3 << std::endl;

	slice3 = ip3::GetMatrixSlice(&test_p,4,4,3);
	std::cout << "Invalid coord (4,4): " << std::endl;
	std::cout << slice3 << std::endl;

	slice3 = ip3::GetMatrixSlice(&test_p,-1,-1,3);
	std::cout << "Invalid coord (-1,-1): " << std::endl;
	std::cout << slice3 << std::endl;

	slice3 = ip3::GetMatrixSlice(&test_p,0,0,7);
	std::cout << "Valid coord (0,0) bad kernel_size (7): " << std::endl;
	std::cout << slice3 << std::endl;

	slice3 = ip3::GetMatrixSlice(&test_p,1,2,3);
	std::cout << "Random valid coord: " << std::endl;
	std::cout << slice3 << std::endl;

	test.release();
	test_p.release();
	slice1.release();
	slice2.release();
	slice3.release();
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
