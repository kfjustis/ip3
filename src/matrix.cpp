#include "matrix.h"

namespace ip3 {
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
}
