#pragma once

#include <cmath>
#include <iostream>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace ip3 {
//#define PI 3.14159265
#define PI 3.14

/*
 * Determines the average of the values in the matrix and returns it.
 * Dimensions must be square for this to work.
 * PARAMS: const cv::Mat* src - address of the source matrix
 * RETURN: double - the calculated average from the matrix, < 0 on failure
 */
double AverageMatrix(const cv::Mat* src);

/*
 * Checks that the dimensions of the slice are a perfect square.
 * PARAMS: const cv::Mat* src - address of the source matrix
 * RETURN: bool - true on success, false on failure
 */
bool CheckSliceDimensions(const cv::Mat* src);

/*
 * Iteratively visits every pixel in the source image and convolves it with
 * the given kernel. Do not pass 0-padded input. The resulting image is returned.
 * PARAMS: const cv::Mat* src - address of the source matrix
 *         const cv::Mat* kernel - address of the kernel matrix
 * RETURN: cv::Mat - the resulting image after convolution, empty matrix on failure
 */
cv::Mat ConvolveImage(const cv::Mat* src, const cv::Mat* kernel);

/*
 * Performs matrix convolution between a given slice and a given kernel.
 * The slice and the kernel must be the same dimensions. Only the calculated value
 * is returned. No replacement in memory occurs.
 * PARAMS: const cv::Mat* slice - address of the source slice
 *         const cv::Mat* kernel - address of the kernel matrix to convolve with
 * RETURN: double - the calculated value after convolution
 */
double ConvolveMatrix(const cv::Mat* slice, const cv::Mat* kernel);

/*
 * Computes the gradient at each pixel value based on the x and y gradient
 * values already calculated from a given source image. If the return
 * matrix is represented with the indentifier "f_full", then:
 *      f_full = sqrt ( f_x^2 + f_y^2 )
 * PARAMS: const cv::Mat* f_x - the gradient representing the x direction
 *         const cv::Mat* f_y - the gradient representing the y direction
 * RETURN: cv::Mat - the matrix containing the full gradient values, empty mat on failure
 */
cv::Mat GetFullGradient(const cv::Mat* f_x, const cv::Mat* f_y);

/*
 * Calculates the orientation of the gradient given matrices representing the
 * the gradient in the x and y direction of the source image. Values are stored in degrees.
 * PARAMS: const cv::Mat* f_x - the gradient representing the x direction
 *         const cv::Mat* f_y - the gradient representing the y direction
 * RETURN: cv::Mat - the matrix containing the gradient orientation at each pixel, empty matrix on failure
 */
cv::Mat GetGradientOrientation(const cv::Mat* f_x, const cv::Mat* f_y);

/*
 * Takes a given matrix and upper left coordinate for a region slice.
 * From that coordinate, a new matrix is generated with data from the requested
 * region.
 * PARAMS: const cv::Mat* src - address of source the source matrix
 *         int row - the top-left row coordinate for desired slice region in src
 *         int col - the top-left col coordinate for desired slice region in src
 *         int kernel_size - the square dimension of the kernel (3 = 3x3)
 * RETURN: cv::Mat - the matrix containing the requested slice, empty matrix on failure
 */
cv::Mat GetMatrixSlice(const cv::Mat* src, int row, int col, int kernel_size);

/*
 * Takes a given matrix and returns the same matrix padded with duplicate values.
 * PARAMS: const cv::Mat* src - reference to source data as an opencv matrix
 * RETURN: a new opencv matrix with padded zeros, empty matrix on failure
 */
cv::Mat PadMatrix(const cv::Mat* src);
} // namespace
