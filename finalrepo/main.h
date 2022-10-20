#pragma once

#ifndef _MAIN_H_
#define _MAIN_H_

#include <cstdio>
#include <iostream>

#include <omp.h>
#include <time.h>
#include<stdlib.h>



#define NUM_THREADS 8

class MyTasker {
public:
	void runTest01_OpenMP(bool Display=false);
	void runTest02_CUDA(bool Display = false);
	void runTest03_SobelSerial(bool Display = false);
	void runTest03_SobelSerial_CV(bool Display = false);
	void runTest04_SobelOmp(bool Display = false);
	void runTest04_SobelOmp_CV(bool Display = false);
	void runTest05_SobelCUDA(bool Display = false);
	void runTest06_SobelMPI(bool Display = false);
	void runTest07_SobelMPIOmp(bool Display = false);
	MyTasker() {};
	~MyTasker() {};
};

#endif