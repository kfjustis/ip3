#include <iostream>
#include <cstdint>
#include <cstring>

#include "matrix.h"
#include "tests.h"

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

		// call tests
		//ip3::TEST_PadMatrix();
		//ip3::TEST_AverageMatrix();
		//ip3::TEST_ConvolveMatrix();
		//ip3::TEST_ConvolveImage();
		//ip3::TEST_GetMatrixSlice();
		//ip3::TEST_MeanFilter(&src_image);
		ip3::TEST_MapOrientation();
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
		std::cout << "\tLow threshold: " << (int) t_l << std::endl << std::endl;

		std::cout << "Calculating filtered gradient...\n" << std::endl;
		// mean filter with 1 iteration
		cv::Mat m_filtered = ip3::MeanFilter(&src_image, (int)sigma);
		//cv::Mat m_filtered = ip3::MeanFilter(&src_image, 0);

		//m_filtered.convertTo(m_filtered, CV_8UC1);
		//m_filtered.convertTo(m_filtered, CV_64F);
		/*cv::namedWindow("Main :: MeanFilter output", CV_WINDOW_AUTOSIZE);
		cv::imshow("Main :: MeanFilter output", m_filtered);
	    cv::waitKey(0);*/

		// generate sobel_x kernel
		cv::Mat sobel_x = cv::Mat::Mat(3, 3, CV_64F);
		sobel_x.at<double>(0,0) = -1;
		sobel_x.at<double>(0,1) = 0;
		sobel_x.at<double>(0,2) = 1;
		sobel_x.at<double>(1,0) = -2;
		sobel_x.at<double>(1,1) = 0;
		sobel_x.at<double>(1,2) = 2;
		sobel_x.at<double>(2,0) = -1;
		sobel_x.at<double>(2,1) = 0;
		sobel_x.at<double>(2,2) = 1;

		// generate sobel_y kernel
		cv::Mat sobel_y = cv::Mat::Mat(3, 3, CV_64F);
		sobel_y.at<double>(0,0) = -1;
		sobel_y.at<double>(0,1) = -2;
		sobel_y.at<double>(0,2) = -1;
		sobel_y.at<double>(1,0) = 0;
		sobel_y.at<double>(1,1) = 0;
		sobel_y.at<double>(1,2) = 0;
		sobel_y.at<double>(2,0) = 1;
		sobel_y.at<double>(2,1) = 2;
		sobel_y.at<double>(2,2) = 1;

		cv::Mat F_x = ip3::ConvolveImage(&m_filtered, &sobel_x);
		cv::Mat F_y = ip3::ConvolveImage(&m_filtered, &sobel_y);
		cv::Mat F_mag = ip3::GetFullGradient(&F_x, &F_y);
		cv::Mat F_orient = ip3::GetGradientOrientation(&F_x, &F_y);

		std::cout << "Executing non-maximum suppression...\n" << std::endl;
		cv::Mat I = ip3::NonMaxSuppress(&F_orient);

		std::cout << "Applying thresholding...\n" << std::endl;
		cv::Mat thresh = ip3::Thresholding(&I, t_h, t_l);

		/*src_image.convertTo(src_image, CV_8UC1);
		cv::namedWindow("Main :: Source input", CV_WINDOW_AUTOSIZE);
		cv::imshow("Main :: ource input", src_image);
		F_x.convertTo(F_x, CV_8UC1);
		cv::namedWindow("Main :: F_x output", CV_WINDOW_AUTOSIZE);
		cv::imshow("Main :: F_x output", F_x);
		F_y.convertTo(F_y, CV_8UC1);
		cv::namedWindow("Main :: F_y output", CV_WINDOW_AUTOSIZE);
		cv::imshow("Main :: F_y output", F_y);
	    cv::waitKey(0);*/
		/*F_mag.convertTo(F_mag, CV_8UC1);
		cv::namedWindow("Main :: F_mag output", CV_WINDOW_AUTOSIZE);
		cv::imshow("Main :: F_mag output", F_mag);
	    cv::waitKey(0);*/
		/*F_orient.convertTo(F_orient, CV_8UC1);
		cv::namedWindow("Main :: F_orient output", CV_WINDOW_AUTOSIZE);
		cv::imshow("Main :: F_orient output", F_orient);
	    cv::waitKey(0);*/
		/*I.convertTo(I, CV_8UC1);
		cv::namedWindow("Main :: NonMaxSuppress output", CV_WINDOW_AUTOSIZE);
		cv::imshow("Main :: NonMaxSuppress output", I);
	    cv::waitKey(0);*/
		thresh.convertTo(I, CV_8UC1);
		cv::namedWindow("Main :: Thresholding output", CV_WINDOW_AUTOSIZE);
		cv::imshow("Main :: Thresholding output", thresh);
	    cv::waitKey(0);

		if (m_filtered.data != NULL) {
			m_filtered.release();
		}
		if (sobel_x.data != NULL) {
			sobel_x.release();
		}
		if (F_x.data != NULL) {
			F_x.release();
		}
		if (F_y.data != NULL) {
			F_y.release();
		}
		if (F_mag.data != NULL) {
			F_mag.release();
		}
		if (F_orient.data != NULL) {
			F_orient.release();
		}
		if (I.data != NULL) {
			I.release();
		}
		if (thresh.data != NULL) {
			thresh.release();
		}
	}

	// cleanup
	if (src_image.data != NULL) {
		src_image.release();
	}
	return 0;
}
