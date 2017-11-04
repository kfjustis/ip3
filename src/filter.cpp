#include "filter.h"

namespace ip3 {
cv::Mat MeanFilter(const cv::Mat* src, int iterations) {
    if (src == NULL) {
        return cv::Mat();
    }

    if (iterations < 0) {
        return cv::Mat();
    }

    // convert the given image to our data type
    cv::Mat output = src->clone();
    output.convertTo(output, CV_64F);

    if (iterations == 0) {
        return output;
    }

    // walk through the matrix and apply the filter "iterations" number of times
    cv::Mat src_clone_p = ip3::PadMatrix(&output);
    cv::Mat slice;
    double average = 0;
    int kernel_size = 3;
    for (int loop = 0; loop < iterations; ++loop) {
        for (int i = 0; i <= (src_clone_p.rows-kernel_size); ++i) {
            for (int j = 0; j <= (src_clone_p.cols-kernel_size); ++j) {
                slice = ip3::GetMatrixSlice(&src_clone_p, i, j, kernel_size);
                average = ip3::AverageMatrix(&slice);
                output.at<double>(i,j) = average;
            }
        }
        // reset for the next iteration
        src_clone_p = ip3::PadMatrix(&output);
    }

    // cleanup and return
    src_clone_p.release();
    slice.release();
    return output;
}
} // namespace
