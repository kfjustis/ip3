#pragma once

#include <cmath>
#include <iostream>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace ip3 {
/*
 * Determines the average of the values in the matrix and returns it.
 * Dimensions must be square for this to work.
 * PARAMS: const cv::Mat* src - address of the source matrix
 * RETURN: int - the calculated average from the matrix, < 0 on failure
 */
int AverageMatrix(const cv::Mat* src);

/*
 * Checks that the dimensions of the slice are a perfect square.
 * PARAMS: const cv::Mat* src - address of the source matrix
 * RETURN: bool - true on success, false on failure
 */
bool CheckSliceDimensions(const cv::Mat* src);

/*
 * Performs matrix convolution between a given slice and a given kernel.
 * The slice and the kernel must be the same dimensions. Only the calculated value
 * is returned. No replacement in memory occurs.
 * PARAMS: const cv::Mat* slice - address of the source slice
 *         const cv::Mat* kernel - address of the kernel matrix to convolve with
 * RETURN: int - the calculated value after convolution
 */
int ConvolveMatrix(const cv::Mat* slice, const cv::Mat* kernel);

/*
 * Takes a given matrix and returns the same matrix padded with zeros.
 * PARAMS: const cv::Mat* src - reference to source data as an opencv matrix
 * RETURN: a new opencv matrix with padded zeros, empty matrix on failure
 */
cv::Mat PadMatrix(const cv::Mat* src);
} // namespace
