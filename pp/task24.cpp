#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int n;
    #pragma omp parallel num_threads(4) private(n)
    {
        n = omp_get_thread_num();
        printf("Значение n (начало): %d\n", n);
        #pragma omp single copyprivate(n)
        {
            n = 100;
        printf("Значение n (конец): %d\n", n);
        }
    }
}
