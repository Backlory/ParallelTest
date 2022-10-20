#include "main.h"
#include "kernel.cuh"

void MyTasker::runTest02_CUDA(bool Display) {
	if (Display) std::cout << "Test02_CUDA starts..." << std::endl;

	checkGPU();

	UnityTest_01_add();

	return;
}