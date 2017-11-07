#include "matrix.h"

namespace ip3 {
double AverageMatrix(const cv::Mat* src) {
	if (src == NULL) {
        return -1;
    }

    if (CheckSliceDimensions(src) == false) {
        return -1;
    }

	//std::cout << "AverageMatrix :: input: " << std::endl;
	//std::cout << src->clone() << std::endl;

	//std::cout << "AverageMatrix :: sums: " << std::endl;
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

	//std::cout << "AverageMatrix :: average is " << (int) average << std::endl;

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

	// create ouput and padded clone of source matrix
	cv::Mat output = src->clone();
	cv::Mat src_clone_p = ip3::PadMatrix(src);
	cv::Mat slice;
	int conv_val = 0;
	for (int i = 0; i < (src_clone_p.rows - kernel->rows+1); ++i) {
		for (int j = 0; j < (src_clone_p.cols - kernel->cols+1); ++j) {
			slice = ip3::GetMatrixSlice(&src_clone_p, i, j, kernel->rows);
			conv_val = ip3::ConvolveMatrix(&slice, kernel);
			output.at<double>(i,j) = conv_val;
		}
	}

	src_clone_p.release();
	slice.release();

	return output;
}

double ConvolveMatrix(const cv::Mat* slice, const cv::Mat* kernel) {
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

	return sum;
}

cv::Mat GetFullGradient(const cv::Mat* f_x, const cv::Mat* f_y) {
	if (f_x == NULL || f_y == NULL) {
		return cv::Mat();
	}

	if (f_x->rows != f_y->rows && f_x->cols != f_y->cols) {
		return cv::Mat();
	}

	// contains the final values for F
	cv::Mat f_f = cv::Mat::Mat(f_x->rows, f_x->cols, CV_64F);

	double value = 0;
	for (int i = 0; i < f_x->rows; ++i) {
		for (int j = 0; j < f_x->cols; ++j) {
			// calculate the values
			value = sqrt(pow(f_x->at<double>(i,j), 2) + pow(f_y->at<double>(i,j), 2));

			// write value to f_f
			f_f.at<double>(i,j) = value;
		}
	}

	return f_f;
}

cv::Mat GetGradientOrientation(const cv::Mat* f_x, const cv::Mat* f_y) {
	if (f_x == NULL || f_y == NULL) {
		return cv::Mat();
	}

	if (f_x->rows != f_y->rows && f_x->cols != f_y->cols) {
		return cv::Mat();
	}

	cv::Mat F_orient = cv::Mat::Mat(f_x->rows, f_x->cols, CV_64F);

	double value = 0, temp_x = 0;
	for (int i = 0; i < f_x->rows; ++i) {
		for (int j = 0; j < f_x->cols; ++j) {
			// calculate orientation in degrees and store in F_orient
			temp_x = f_x->at<double>(i,j);
			if (temp_x == 0) {
				temp_x = 1.0;
			}
			value = atan(f_y->at<double>(i,j)/temp_x) * 180.0 / PI;
			F_orient.at<double>(i,j) = value;
		}
	}

	return F_orient;
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
		for (j = col; j < (col + kernel_size); ++j, ++l) {
			if (l == kernel_size) {
				l = 0;
			}
			slice.at<double>(k,l) = src->at<double>(i,j);
		}
	}

	return slice;
}

double MapOrientation(const double* input) {
	if (input == NULL) {
		return -1;
	}
	if (*input > 360 || *input < -360) {
		return -1;
	}

	double output = -1;

	// map orientation as follows
	if (*input >= -45/2 && *input < 45/2) {
		output = 0; //0
	} else if (*input >= 45/2 && *input < (45 + (45/2))) {
		output = 1; //45
	} else if (*input >= (45 + (45/2)) && *input < (90 + (45/2))) {
		output = 2; //90
	} else if (*input >= (90 + (45/2)) && *input < (135 + (45/2))) {
		output = 3; //135
	} else if (*input >= (135 + (45/2)) && *input < (180 + (45/2))) {
		output = 0;
	} else if (*input >= (180 + (45/2)) && *input < (225 + (45/2))) {
		output = 1;
	} else if (*input >= (225 + (45/2)) && *input < (270 + (45/2))) {
		output = 2;
	} else if (*input >= (270 + (45/2)) && *input < (315 + (45/2))) {
		output = 3;
	}

	return output;
}

cv::Mat PadMatrix(const cv::Mat* src) {
	if (src == NULL) {
		return cv::Mat();
	}

	cv::Mat src_clone = src->clone();
	src_clone.convertTo(src_clone, CV_64F);

	// generate padded matrix
	int p_rows = src->rows+2;
	int p_cols = src->cols+2;
	cv::Mat p_mat = cv::Mat::Mat(p_rows, p_cols, CV_64F);

	for (int row = 0; row < p_mat.rows; ++row) {
		for (int col = 0; col < p_mat.cols; ++col) {
			if (row == 0 && col == 0) { // TL
				p_mat.at<double>(row, col) = 0;
			} else if (row == 0 && col == p_mat.cols-1) { // TR
				p_mat.at<double>(row, col) = 0;
			} else if (row == p_mat.rows-1 && col == 0) { // BL
				p_mat.at<double>(row, col) = 0;
			} else if (row == p_mat.rows-1 && p_mat.cols-1) { // BR
				p_mat.at<double>(row, col) = 0;
			} else if (row == 0) { // top row
				p_mat.at<double>(row,col) = src_clone.at<double>(row,col-1);
			} else if (col == 0) { // left col
				p_mat.at<double>(row,col) = src_clone.at<double>(row-1,col);
			} else if (col == p_mat.cols-1) { // right col
				p_mat.at<double>(row,col) = src_clone.at<double>(row-1,col-2);
			} else { // middle
				p_mat.at<double>(row,col) = src_clone.at<double>(row-1, col-1);
			}
		}
	}
	// add values to the bottom row manually
	int c = 1;
	for (int i = p_mat.rows-1; c < p_mat.cols; ++c) {
		p_mat.at<double>(i,c) = src_clone.at<double>(i-2,c-1);
	}
	p_mat.at<double>(p_mat.rows-1, 0) = 0;
	p_mat.at<double>(p_mat.rows-1, p_mat.cols-1) = 0;

	src_clone.release();
	return p_mat;
}
} // namespace
