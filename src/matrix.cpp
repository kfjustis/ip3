#include "matrix.h"

namespace ip3 {
int AverageMatrix(const cv::Mat* src) {
	if (src == NULL) {
        return -1;
    }

    if (CheckSliceDimensions(src) == false) {
        return -2;
    }

    // sum the elements
    double sum = 0;
    for (int i = 0; i < src->rows; ++i) {
        for (int j = 0; j < src->cols; ++j) {
            sum += src->at<double>(i,j);
        }
    }

	//std::cout << "AverageMatrix :: sum is " << sum << std::endl;

    // calculate average
    double total = src->rows * src->cols;
    double average = round((sum / total));

	//std::cout << "AverageMatrix :: average is " << average << std::endl;

    return average;
}

bool CheckSliceDimensions(const cv::Mat* src) {
	if (src == NULL) {
        return false;
    }

    int dim_sqr = src->rows * src->cols;
    int root = (int)sqrt(dim_sqr);
    if (root != src->rows || root != src->cols) {
        return false;
    }

    return true;
}

cv::Mat PadMatrix(const cv::Mat* src) {
	if (src == NULL) {
		return cv::Mat();
	}

	// generate padded matrix
	int p_rows = src->rows+2;
	int p_cols = src->cols+2;
	cv::Mat p_mat = cv::Mat::Mat(p_rows, p_cols, CV_64F);

	for (int row = 0; row < p_mat.rows; ++row) {
		for (int col = 0; col < p_mat.cols; ++col) {
			if (row == 0 || col == 0) {
				p_mat.at<double>(row, col) = 0;
			} else if (row == p_mat.rows-1 || col == p_mat.cols-1) {
				p_mat.at<double>(row, col) = 0;
			} else {
				p_mat.at<double>(row, col) = src->at<double>(row-1, col-1);
			}
		}
	}
	return p_mat;
}

} // namespace
