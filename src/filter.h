#pragma once

#include <iostream>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "matrix.h"

namespace ip3 {
/*
 * Applies mean smoothing filter to the passed source matrix.
 * PARAMS: const cv::Mat* src - address of the source matrix
 *         int iterations - the number of times to apply mean filter
 * RETURN: cv::Mat - the resulting matrix after mean filter convolution, empty matrix on failure
 */
cv::Mat MeanFilter(const cv::Mat* src, int iterations);
} // namespace