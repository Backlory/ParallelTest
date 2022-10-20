#include "main.h"
#define TES_NUM 10.0


auto m = _putenv_s("aaa", "ads");
auto m2 = std::getenv("aaa");


int main(int argc, char* argv[]) {
    std::cout << m << std::endl;
    std::cout << m2 << std::endl;

    MyTasker myTasker = MyTasker();
    
    std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
    myTasker.runTest01_OpenMP(true);
    

    std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
    myTasker.runTest02_CUDA(true);
    

    std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
    myTasker.runTest03_SobelSerial(true);
    time_t t0 = clock();
    for (int i = 0; i < TES_NUM; i++)
        myTasker.runTest03_SobelSerial();
    std::cout << "----Average time cost = " << (clock() - t0) / TES_NUM << " ms" << std::endl;
    

    std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
    myTasker.runTest03_SobelSerial_CV(true);
    t0 = clock();
    for (int i = 0; i < TES_NUM; i++)
        myTasker.runTest03_SobelSerial_CV();
    std::cout << "----Average time cost = " << (clock() - t0) / TES_NUM << " ms" << std::endl;


    std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
    myTasker.runTest04_SobelOmp(true);
    t0 = clock();
    for (int i = 0; i < TES_NUM; i++)
        myTasker.runTest04_SobelOmp();
    std::cout << "----Average time cost = " << (clock() - t0) / TES_NUM << " ms" << std::endl;


    std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
    myTasker.runTest04_SobelOmp_CV(true);
    t0 = clock();
    for (int i = 0; i < TES_NUM; i++)
        myTasker.runTest04_SobelOmp_CV();
    std::cout << "----Average time cost = " << (clock() - t0) / TES_NUM << " ms" << std::endl;


    std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
    myTasker.runTest05_SobelCUDA(true);
    t0 = clock();
    for (int i = 0; i < TES_NUM; i++)
        myTasker.runTest05_SobelCUDA();
    std::cout << "----Average time cost = " << (clock() - t0) / TES_NUM << " ms" << std::endl;


    std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
    myTasker.runTest06_SobelMPI(true);
    t0 = clock();
    for (int i = 0; i < TES_NUM; i++)
        myTasker.runTest06_SobelMPI();
    std::cout << "----Average time cost = " << (clock() - t0) / TES_NUM << " ms" << std::endl;


    std::cout << std::endl << std::endl << std::endl << std::endl << "============================================" << std::endl;
    myTasker.runTest07_SobelMPIOmp(true);
    t0 = clock();
    for (int i = 0; i < TES_NUM; i++)
        myTasker.runTest07_SobelMPIOmp();
    std::cout << "----Average time cost = " << (clock() - t0) / TES_NUM << " ms" << std::endl;
    return 0;
}
