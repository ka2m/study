#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int n=1;
    printf("n в последовательной области (начало): %d\n", n);
#pragma omp parallel num_threads(4) private(n)
    {
        printf("Значение n в потоке (на входе): %d\n", n);
        n=omp_get_thread_num();
        printf("Значение n в потоке (на выходе): %d\n", n);
    }
    printf("n в последовательной области (конец): %d\n", n);
}
