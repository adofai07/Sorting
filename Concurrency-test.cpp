#include <stdio.h>
#include <omp.h>

#define MAX_THREADS 8

int main(void) {
    omp_set_num_threads(MAX_THREADS);
    int a = 0;

    #pragma omp parallel
    {
        const int thr = omp_get_thread_num();
        printf("[%d] Hello, world. (%d)\n", thr, a++);
    }


    return 0;
}