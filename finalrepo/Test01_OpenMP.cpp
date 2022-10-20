#include "main.h"

void MyTasker::runTest01_OpenMP(bool Display){
    if (Display) std::cout << "Test01_OpenMP starts..." << std::endl;
    int nthreads, tid;
#pragma omp parallel private(tid) 
    {
        tid = omp_get_thread_num();
        if (Display) printf("Hello World from thread = %d\n", tid);

        if (tid == 0) {
            nthreads = omp_get_num_threads();
            if (Display) printf("Number of threads = %d\n", nthreads);
        }
    }

#pragma omp parallel for collapse(2) num_threads(8) private(tid) 
    for (int i=0; i<3; i++) {
        for (int j = 0; j < 40; j++) {
            tid = omp_get_thread_num();
            if (Display) printf("id=%d, %d, thread = %d\n", i, j, tid);
        }
    }

    return;
}