#include "main.h"
#define TES_NUM 10.0

int main(int argc, char* argv[]) {
    MyTasker myTasker = MyTasker();
    std::vector<int> taskswitch{ 1,1,0,0,0,0,0,0,0,0,0,0 };
    
    if (taskswitch[0]) {
        std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
        myTasker.runTest01_OpenMP(true);
    }
    

    if (taskswitch[1]) {
        std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
        myTasker.runTest02_CUDA(true);
    }
    

    if (taskswitch[2]) {
        std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
        myTasker.runTest03_SobelSerial(true);
        time_t t0 = clock();
        for (int i = 0; i < TES_NUM; i++)
            myTasker.runTest03_SobelSerial();
        std::cout << "----Average time cost = " << (clock() - t0) / TES_NUM << " ms" << std::endl;
    }
    

    if (taskswitch[3]) {
        std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
        myTasker.runTest03_SobelSerial_CV(true);
        time_t t0 = clock();
        for (int i = 0; i < TES_NUM; i++)
            myTasker.runTest03_SobelSerial_CV();
        std::cout << "----Average time cost = " << (clock() - t0) / TES_NUM << " ms" << std::endl;
    }

    if (taskswitch[4]) {
        std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
        myTasker.runTest04_SobelOmp(true);
        time_t t0 = clock();
        for (int i = 0; i < TES_NUM; i++)
            myTasker.runTest04_SobelOmp();
        std::cout << "----Average time cost = " << (clock() - t0) / TES_NUM << " ms" << std::endl;
    }

    if (taskswitch[5]) {
        std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
        myTasker.runTest04_SobelOmp_CV(true);
        time_t t0 = clock();
        for (int i = 0; i < TES_NUM; i++)
            myTasker.runTest04_SobelOmp_CV();
        std::cout << "----Average time cost = " << (clock() - t0) / TES_NUM << " ms" << std::endl;
    }


    if (taskswitch[6]) {
        std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
        myTasker.runTest05_SobelCUDA(true);
        time_t t0 = clock();
        for (int i = 0; i < TES_NUM; i++)
            myTasker.runTest05_SobelCUDA();
        std::cout << "----Average time cost = " << (clock() - t0) / TES_NUM << " ms" << std::endl;
    }


    if (taskswitch[7]) {
        std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
        myTasker.runTest06_SobelMPI(true);
        time_t t0 = clock();
        for (int i = 0; i < TES_NUM; i++)
            myTasker.runTest06_SobelMPI();
        std::cout << "----Average time cost = " << (clock() - t0) / TES_NUM << " ms" << std::endl;
    }


    if (taskswitch[8]) {
        std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
        myTasker.runTest07_SobelMPIOmp(true);
        time_t t0 = clock();
        for (int i = 0; i < TES_NUM; i++)
            myTasker.runTest07_SobelMPIOmp();
        std::cout << "----Average time cost = " << (clock() - t0) / TES_NUM << " ms" << std::endl;
    }
    return 0;
}
