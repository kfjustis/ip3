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

cv::Mat NonMaxSuppress(const cv::Mat* F_orient) {
    if (F_orient == NULL) {
        return cv::Mat();
    }

    double D_orientation = 0;
    double D_star_orientation = 0;
    for (int i = 0; i < F_orient->rows; ++i) {
        for (int j = 0; j < F_orient->cols; ++j) {
            /* for each pixel, find D* in (0, 45, 90, 135) that
            is closest to the orientation D at that pixel */
            D_orientation = F_orient->at<double>(i,j);
            D_star_orientation = ip3::MapOrientation(&D_orientation);
            /*if (D_orientation >= -45/2 || D_orientation < 45/2) {
                D_star_orientation = 0; //0
            } else if (D_orientation >= 45/2 || D_orientation < (45 + (45/2))) {
                D_star_orientation = 1; //45
            } else if (D_orientation >= (45 + (45/2)) || D_orientation < (90 + (45/2)) {
                D_star_orientation = 2; //90
            } else if (D_orientation >= (90 + (45/2) || D_orientation < (135 + (45/2))) {
                D_star_orientation = 3; //135
            } else if (D_orientation >= (135 + (45/2)) || D_orientation < (180 + (45/2))) {
                D_star_orientation = 0;
            } else if (D_orientation >= (180 + (45/2)) || D_orientation < (225 + (45/2))) {
                D_star_orientation = 1;
            } else if (D_orientation >= (225 + (45/2)) || D_orientation < (270 + (45/2))) {
                D_star_orientation = 2;
            } else if (D_orientation >= (270 + (45/2)) || D_orientation < (315 + (45/2))) {
                D_star_orientation = 3;
            }*/
        }
    }
}
} // namespace
