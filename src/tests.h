#pragma once

#include <iostream>

#include "filter.h"
#include "matrix.h"

namespace ip3 {
void TEST_AverageMatrix();

// Source: http://www.songho.ca/dsp/convolution/convolution2d_example.html
void TEST_ConvolveImage();

void TEST_ConvolveMatrix();

void TEST_GetMatrixSlice();

void TEST_MapOrientation();

void TEST_MeanFilter(const cv::Mat* src);

void TEST_PadMatrix();
} // namespace
