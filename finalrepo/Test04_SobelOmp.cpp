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

#include "imgutils.h"
#include <FreeImage.h>

int const sobel_weight_x[3][3] = {
    { -1, 0, 1 },
    { -2, 0, 2 },
    { -1, 0, 1 }
};

int const sobel_weight_y[3][3] = {
    { -1, -2, -1 },
    {  0,  0,  0 },
    {  1,  2,  1 }
};

void sobel_filtering_04(FIBITMAP* imgIn, FIBITMAP* imgOut, bool Display)
{
    omp_set_dynamic(false);
    omp_set_num_threads(NUM_THREADS);

    int width = FreeImage_GetWidth(imgIn);
    assert(width == FreeImage_GetWidth(imgOut));

    int height = FreeImage_GetHeight(imgIn);
    assert(height == FreeImage_GetHeight(imgOut));
    assert(FreeImage_GetBPP(imgIn) == FreeImage_GetBPP(imgOut));

    int widthBytes = FreeImage_GetLine(imgIn);
    int pitch = FreeImage_GetPitch(imgIn);
    int chNum = 0;
    switch (FreeImage_GetBPP(imgIn))
    {
    case 8: chNum = 1; break;
    case 24: chNum = 3; break;
    case 32: chNum = 4; break;
    default:
        if (Display) std::cout << "Unsupported image format!" << std::endl;
        break;
    }

    if (chNum == 0) return;

    if (Display) std::cout << "Filtering of input image start ..." << std::endl;
    double start_time = omp_get_wtime();

    double pixel_value_min, pixel_value_max;
    pixel_value_min = DBL_MAX;
    pixel_value_max = -DBL_MAX;
    BYTE* dataIn = FreeImage_GetBits(imgIn);

    int actual_threads_num = 0;
#if defined(_MSC_VER)
#pragma omp parallel for
#else
#pragma omp parallel for collapse(2)
#endif
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            double pixel_value_x = 0.0;
            double pixel_value_y = 0.0;
            double pixel_value = 0.0;
            for (int j = -1; j <= 1; ++j) {
                for (int i = -1; i <= 1; ++i) {
                    pixel_value_x += sobel_weight_x[j + 1][i + 1] * imgutils::to_gray(dataIn, x + i, y + j, pitch, chNum);
                    pixel_value_y += sobel_weight_y[j + 1][i + 1] * imgutils::to_gray(dataIn, x + i, y + j, pitch, chNum);
                }
            }
            pixel_value = sqrt((pixel_value_x * pixel_value_x) + (pixel_value_y * pixel_value_y));
            actual_threads_num = omp_get_num_threads();
#pragma omp critical
            {
                if (pixel_value < pixel_value_min) pixel_value_min = pixel_value;
                if (pixel_value > pixel_value_max) pixel_value_max = pixel_value;
            }
        }
    }
    if (Display) std::cout << "the minimum value: " << pixel_value_min << std::endl;
    if (Display) std::cout << "the maximum value: " << pixel_value_max << std::endl;
    if (Display) std::cout << "actual threads number: " << actual_threads_num << std::endl;
    if ((int)(pixel_value_max - pixel_value_min) == 0) {
        if (Display) std::cout << "Nothing exists!!!" << std::endl;
        return;
    }

    /* Initialization of imgOut */
    BYTE* dataOut = FreeImage_GetBits(imgOut);
    //#if defined(_MSC_VER)
    //#pragma omp parallel for
    //#else
    //#pragma omp parallel for collapse(2)
    //#endif
        //for (int y = 0; y < height; ++y) {
        //	for (int x = 0; x < pitch; ++x) {
        //		dataOut[y*pitch+x] = 0;
        //	}
        //}
    memset(dataOut, 0, height * pitch);

    /* Generation of imgOut after linear transformation */
#if defined(_MSC_VER)
#pragma omp parallel for
#else
#pragma omp parallel for collapse(2)
#endif
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; x++) {
            double pixel_value_x = 0.0;
            double pixel_value_y = 0.0;
            double pixel_value = 0.0;
            for (int j = -1; j <= 1; ++j) {
                for (int i = -1; i <= 1; ++i) {
                    pixel_value_x += sobel_weight_x[j + 1][i + 1] * imgutils::to_gray(dataIn, x + i, y + j, pitch, chNum);
                    pixel_value_y += sobel_weight_y[j + 1][i + 1] * imgutils::to_gray(dataIn, x + i, y + j, pitch, chNum);
                }
            }
            pixel_value = sqrt((pixel_value_x * pixel_value_x) + (pixel_value_y * pixel_value_y));
            pixel_value = 255.0 * (pixel_value - pixel_value_min) / (pixel_value_max - pixel_value_min);
            imgutils::set_pixel(dataOut, (BYTE)pixel_value, x, y, pitch, chNum);
            //if (Display) printf("For - For - Hello World from thread = %d\n", omp_get_thread_num()); //只有最外层并行了
        }
        //if (Display) printf("For - Hello World from thread = %d\n", omp_get_thread_num());
    }
    if (Display) std::cout << "The total time for execution is " << omp_get_wtime() - start_time << "s" << std::endl;
}



int sobelFunc_Omp(const char imgpath[], bool Display)
{

    FIBITMAP* imgIn = imgutils::load_image(imgpath, 0);
    if (!imgIn) {
        return -1;
    }

    FIBITMAP* imgOut = FreeImage_Clone(imgIn);

    sobel_filtering_04(imgIn, imgOut, Display);

    std::string fnIn(imgpath);
    std::size_t found = fnIn.find_last_of('.');
    std::string fnOut = fnIn.substr(0, found) + "_SobelOmp_FI" + fnIn.substr(found);

    int r = 0;
    if (!imgutils::save_image(fnOut.c_str(), imgOut, 0)) {
        if (Display) std::cout << "Failed to save output image file " << fnOut << std::endl;
        r = -2;
    }

    FreeImage_Unload(imgIn);
    FreeImage_Unload(imgOut);
    return r;
}



void MyTasker::runTest04_SobelOmp(bool Display) {
	if (Display) std::cout << "Test04_SobelOmp starts..." << std::endl;

    char imgpath[] = R"(F:\CPPprojs\221003-finalrepo\finalrepo\testimg.jpeg)";

	int out = sobelFunc_Omp(imgpath, Display);
	if (Display) std::cout << out << std::endl;
	return;
}