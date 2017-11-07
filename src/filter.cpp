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

    cv::Mat output = cv::Mat::Mat(F_orient->rows, F_orient->cols, CV_64F);
    cv::Mat padded = F_orient->clone();
    padded = ip3::PadMatrix(&padded);
    padded.convertTo(padded, CV_64F);
    cv::Mat slice;

    double curr_orient = -500; // not a possible value
    double curr_slice_val = -500;
    for (int i = 0; i < padded.rows-slice.rows+1; ++i) {
        for (int j = 0; j < padded.cols-slice.cols+1; ++j) {
            slice = ip3::GetMatrixSlice(&padded,i,j,3);

            // the orientation of the current value we're inspecting
            curr_orient = ip3::MapOrientation(&(slice.at<double>(1,1)));

            // evaluate neighbors
            /* if any are greater than the center value along the same orientation,
             * set the same coordinate in the output to 0, otherwise, use it's value */
            for (int k = 0; k < slice.rows; ++k) {
                for (int l = 0; l < slice.cols; ++l) {
                    if (ip3::MapOrientation(&(slice.at<double>(k,l))) == curr_orient) {
                        // these values match the orientation of the checked values
                        curr_slice_val = slice.at<double>(k,l);
                        if (curr_slice_val > slice.at<double>(1,1)) {
                            // set I(x,y) (the output) = 0, else same value
                            output.at<double>(i+k, j+l) = 0;
                            //output.at<double>(i, j) = 0;
                        } else {
                            output.at<double>(i+k, j+l) = curr_slice_val;
                            //output.at<double>(i, j) = curr_slice_val;
                        }
                    }
                }
            }
        }
    }

    return output;
}

cv::Mat Thresholding(const cv::Mat* nmax_mat, uint8_t t_h, uint8_t t_l) {
    if (nmax_mat == NULL) {
        return cv::Mat();
    }

    cv::Mat output = nmax_mat->clone();
    cv::Mat visited = cv::Mat::Mat(output.rows, output.cols, CV_64F, double(0));

    for (int i = 0; i < output.rows; ++i) {
        for (int j = 0; j < output.cols; ++j) {
            // do stuff
            if (visited.at<double>(i,j) != 1 && nmax_mat->at<double>(i,j) > t_h) {
                if (nmax_mat->at<double>(i,j) > t_l) {
                    output.at<double>(i,j) = 255;
                } else {
                    output.at<double>(i,j) = 0;
                }
                visited.at<double>(i,j) = 1;
            }
        }
    }
    return output;
}
} // namespace
