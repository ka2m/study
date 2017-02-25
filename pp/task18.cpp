#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int n;
    omp_set_dynamic(0);
    omp_set_num_threads(3);
    omp_set_nested(1);
#pragma omp parallel private(n)
    {
        n=omp_get_thread_num();
#pragma omp parallel
        {
            printf("Part 1, thread %d - %d\n", n,
                    omp_get_thread_num());
        }
    }
    omp_set_nested(0);
#pragma omp parallel private(n)
    {
        n=omp_get_thread_num();
#pragma omp parallel
        {
            printf("Part 2, thread %d - %d\n", n,
                    omp_get_thread_num());
        }
    }
}
