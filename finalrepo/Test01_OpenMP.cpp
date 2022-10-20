#include "main.h"

using std::cout;
using std::endl;

void t01f1(bool Display);
void t01f2(bool Display);

void t01f1(bool Display)
{
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
}

void t01f2(bool Display)
{
    int j, k, a;
#pragma omp parallel num_threads(2)
    {
#pragma omp for collapse(2) ordered private(j, k) schedule(static,3)
        for (k = 1; k <= 3; k++)
            for (j = 1; j <= 2; j++)
            {
#pragma omp ordered
                printf(" %d %d %d\n", omp_get_thread_num(), k, j);
                ;
            }
    }
}

void MyTasker::runTest01_OpenMP(bool Display){
    if (Display) std::cout << "Test01_OpenMP starts..." << std::endl;

    t01f1(Display);
    t01f2(Display);

    return;

}