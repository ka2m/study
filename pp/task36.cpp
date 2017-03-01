//OMP_Sections
#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[]) {
    int n;
#pragma omp parallel num_threads(3) private(n)
    {
        n=omp_get_thread_num();
#pragma omp sections
        {
#pragma omp section
            {
                printf("Первая секция, поток %d\n", n);
            }
#pragma omp section
            {
                printf("Вторая секция, поток %d\n", n);
            }
#pragma omp section
            {
                printf("Третья секция, поток %d\n", n);
            }
#pragma omp section
            {
                printf("Четвертая секция, поток %d\n", n);
            }
#pragma omp section
            {
                printf("Пятая секция, поток %d\n", n);
            }
        }
        printf("Параллельная область, поток %d\n", n);
    }
}
