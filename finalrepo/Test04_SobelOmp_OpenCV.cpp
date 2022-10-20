#pragma once

#include "main.h"

#include <float.h>
#include <assert.h>
#include <omp.h>
#include <math.h>

#include <vector>
#include <iostream>
#include <string>
#include <cstring>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>


const cv::Mat sobel_weight_x = (cv::Mat_<double>(3, 3) << -1, 0, 1,
    -2, 0, 2,
    -1, 0, 1);

const cv::Mat sobel_weight_y = (cv::Mat_<double>(3, 3) << -1, -2, -1,
    0, 0, 0,
    1, 2, 1);

void sobel_filtering_04_CV(cv::Mat& imgIn, cv::Mat& imgOut, bool Display)
{

    omp_set_dynamic(false);
    omp_set_num_threads(NUM_THREADS);
 
    int width = imgIn.cols;
    int height = imgIn.rows;
    assert(width == imgOut.cols);
    assert(height == imgOut.rows);
    assert(imgIn.channels() == imgOut.channels());
    assert(imgIn.type() == CV_8UC1);
    auto chNum = imgIn.channels();
    if (chNum == 0) return;

    if (Display) std::cout << "Filtering of input image start ..." << std::endl;
    double start_time = omp_get_wtime();

    double pixel_value_min, pixel_value_max;
    pixel_value_min = DBL_MAX;
    pixel_value_max = -DBL_MAX;

    int actual_threads_num = 0;

//#pragma omp parallel for shared(sobel_weight_x, sobel_weight_y, imgIn) 
//#pragma omp parallel for private(pixel_value_x, pixel_value_y, pixel_value)
#pragma omp parallel for collapse(2)
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            //pixel_value_x = 0;
            //pixel_value_y = 0;

            double pixel_value_x = 0.0;
            double pixel_value_y = 0.0;
            double pixel_value = 0.0;
            for (int j = -1; j <= 1; ++j) {
                for (int i = -1; i <= 1; ++i) {
                    pixel_value_x += sobel_weight_x.at<double>(j + 1, i + 1) * imgIn.at<uchar>(y + j, x + i);
                    pixel_value_y += sobel_weight_y.at<double>(j + 1, i + 1) * imgIn.at<uchar>(y + j, x + i);
                }
            }
            pixel_value = sqrt((pixel_value_x * pixel_value_x) + (pixel_value_y * pixel_value_y));
            actual_threads_num = omp_get_num_threads();
#pragma omp critical 
            {
            if (pixel_value < pixel_value_min) pixel_value_min = pixel_value;
            if (pixel_value > pixel_value_max) pixel_value_max = pixel_value;
            }
        if (Display) printf("For - For - Hello World from thread = %d\n", omp_get_thread_num()); //ֻ������㲢����
        }
    if (Display) printf("For - Hello World from thread = %d\n", omp_get_thread_num()); //ֻ������㲢����

    }
    if (Display) std::cout << "the minimum value: " << pixel_value_min << std::endl;
    if (Display) std::cout << "the maximum value: " << pixel_value_max << std::endl;
    if (Display) std::cout << "actual threads number: " << actual_threads_num << std::endl;
    if ((int)(pixel_value_max - pixel_value_min) == 0) {
        if (Display) std::cout << "Nothing exists!!!" << std::endl;
        return;
    }
    if (Display) std::cout << "The step time for execution is " << omp_get_wtime() - start_time << "s" << std::endl;

    /* Generation of imgOut after linear transformation */

#pragma omp parallel for collapse(2)
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; x++) {
            double pixel_value_x = 0.0;
            double pixel_value_y = 0.0;
            double pixel_value = 0.0;
            for (int j = -1; j <= 1; ++j) {
                for (int i = -1; i <= 1; ++i) {
                    pixel_value_x += sobel_weight_x.at<double>(j + 1, i + 1) * imgIn.at<uchar>(y + j, x + i);
                    pixel_value_y += sobel_weight_y.at<double>(j + 1, i + 1) * imgIn.at<uchar>(y + j, x + i);
                }
            }
            pixel_value = sqrt((pixel_value_x * pixel_value_x) + (pixel_value_y * pixel_value_y));
            pixel_value = 255.0 * (pixel_value - pixel_value_min) / (pixel_value_max - pixel_value_min);
            imgOut.at<uchar>(y, x) = (uchar)(pixel_value);
        }
    }

    if (Display) std::cout << "The total time for execution is " << omp_get_wtime() - start_time << "s" << std::endl;
}

/* imgpath:  R"(F:\CPPprojs\221003-finalrepo\finalrepo\testimg.jpeg)"
*/
int sobelFunc_04_CV(const std::string imgpath, bool Display)
{
    cv::Mat imgIn = cv::imread(imgpath, 1);
    if (imgIn.empty()) {
        return -1;
    }

    std::vector<cv::Mat> c;
    cv::split(imgIn, c);
    cv::Mat imgIn_gray;
    cv::addWeighted(c.at(0), 0.5, c.at(1), 0.5, 0, imgIn_gray);
    cv::addWeighted(imgIn_gray, 0.666666666, c.at(2), 0.333333333, 0, imgIn_gray);
    cv::Mat imgOut = imgIn_gray.clone();

    sobel_filtering_04_CV(imgIn_gray, imgOut, Display);

    std::string fnIn(imgpath);
    std::size_t found = fnIn.find_last_of('.');
    std::string fnOut = fnIn.substr(0, found) + "_SobelSerial_CV" + fnIn.substr(found);

    int r = 0;
    if (!cv::imwrite(fnOut, imgOut)) {
        if (Display) std::cout << "Failed to save output image file " << fnOut << std::endl;
        r = -2;
    }

    return r;
}



void MyTasker::runTest04_SobelOmp_CV(bool Display) {
    if (Display) std::cout << "Test04_SobelOmp_CV starts..." << std::endl;

    std::string imgpath{ R"(F:\CPPprojs\221003-finalrepo\finalrepo\testimg.jpeg)" };

    int out = sobelFunc_04_CV(imgpath, Display);
    if (Display) std::cout << out << std::endl;
    return;
}

