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

cv::Mat ConvolveImage(const cv::Mat* src, const cv::Mat* kernel) {
	if (src == NULL || kernel == NULL) {
		return cv::Mat();
	}

	// clone and pad the source matrix
	cv::Mat src_clone_p = ip3::PadMatrix(src);

	// TODO implement GETMATRIXSLICE

	src_clone_p.release();

	return cv::Mat();
}

int ConvolveMatrix(const cv::Mat* slice, const cv::Mat* kernel) {
	if (slice == NULL || kernel == NULL) {
		return -1;
	}

	// check that both mats are equal size
	if (slice->rows != kernel->rows || slice->cols != kernel-> cols) {
		return -1;
	}

	// loop through and convolve
	double sum = 0;
	for (int i = 0; i < slice->rows; ++i) {
		for (int j = 0; j < slice->cols; ++j) {
			sum += slice->at<double>(i,j) * kernel->at<double>(i,j);
		}
	}

	return (int) sum;
}

cv::Mat GetMatrixSlice(const cv::Mat* src, int row, int col, int kernel_size) {
	if (src == NULL) {
		return cv::Mat();
	}

	// check coordinates and kernel size
	// invalid coordinates
	if (row < 0 || col < 0) {
		return cv::Mat();
	}
	// out of bounds coordinates
	if (row > src->rows || col > src->cols) {
		return cv::Mat();
	}
	// invalid kernel size
	if (kernel_size <= 0) {
		return cv::Mat();
	}
	// kernel larger than entire source matrix
	if (kernel_size * kernel_size > src->rows * src->cols) {
		return cv::Mat();
	}
	// kernel would have to extend beyond source bounds
	if (row + kernel_size-1 > src->rows || col + kernel_size-1 > src->cols) {
		return cv::Mat();
	}

	// generate slice matrix and load data from source image
	cv::Mat slice;

	// if kernel same size as source, just return source
	if (kernel_size * kernel_size == src->rows * src->cols) {
		slice = src->clone();
		return slice;
	} else {
		slice  = cv::Mat::Mat(kernel_size, kernel_size, CV_64F);
	}

	// copy the data from source into slice
	int i = 0, j = 0, k = 0, l = 0;
	for (i = row; i < (row + kernel_size); ++i, ++k) {
		if (k == kernel_size) {
			k = 0;
		}
		for (j = col; j < (col + kernel_size); ++j, ++l) {
			if (l == kernel_size) {
				l = 0;
			}
			slice.at<double>(k,l) = src->at<double>(i,j);
		}
	}

	return slice;
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
