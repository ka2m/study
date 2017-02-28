#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int n=1;
    printf("Значение n в начале: %d\n", n);
#pragma omp parallel num_threads(4) firstprivate(n)
    {
        printf("Значение n в потоке (на входе): %d\n", n);
        /* Присвоим переменной n номер текущей нити */
        n=omp_get_thread_num();
        printf("Значение n в потоке (на выходе): %d\n", n);
    }
    printf("Значение n в конце: %d\n", n);
}
