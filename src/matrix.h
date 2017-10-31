#pragma once

#include <cmath>
#include <iostream>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace ip3 {

/*
 * Takes a given matrix and returns the same matrix padded with zeros.
 * PARAMS: const cv::Mat* src - reference to source data as an opencv matrix
 * RETURN: a new opencv matrix with padded zeros, empty matrix on failure
 */
cv::Mat PadMatrix(const cv::Mat* src);

} // namespace
