#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int n;
#pragma omp parallel num_threads(4)
    {
#pragma omp critical
        {
            n=omp_get_thread_num();
            printf("Thread %d\n", n);
        }
    }
}
