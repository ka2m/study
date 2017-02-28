#include <stdio.h>
#include <omp.h>
#include <unistd.h>

omp_lock_t lock;

int main(int argc, char *argv[]) {
    int n;
    omp_init_lock(&lock);
#pragma omp parallel num_threads(4) private (n)
    {
        n=omp_get_thread_num();
        while (!omp_test_lock (&lock))
        {
            printf("Секция закрыта, поток %d\n", n);
            sleep(1);
        }
        printf("Начало закрытой секции, поток %d\n", n);
        sleep(3);
        printf("Конец закрытой секции, поток %d\n", n);
        omp_unset_lock(&lock);
    }
    omp_destroy_lock(&lock);
}
