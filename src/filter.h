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

/*
 * Performs non-maximum suppression against a given matrix containing the source image's
 * gradient orientation.
 * PARAMS: const cv::Mat* F_orient - matrix containing the gradient orientation for each pixel in degrees
 * RETURN: cv::Mat - matrix containing the suppressed and non-suppressed values, empty matrix on failure
 */
 cv::Mat NonMaxSuppress(const cv::Mat* F_orient);

/* Performs hysteresis thresholding on a non-max suppressed image.
 * PARAMS: const cv::Mat* nmax_mat - address of matrix containing non-max suppressed image
 *         uint8_t t_h - high value used for thresholding
 *         uint8_t t_l - low value used for thresholding
 * RETURN: cv::Mat - matrix containing the final output image, empty matrix on failure
 */
 cv::Mat Thresholding(const cv::Mat* nmax_mat, uint8_t t_h, uint8_t t_l);
} // namespace
