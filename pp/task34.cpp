#include <stdio.h>
#include <omp.h>
#include <locale.h>
#define NN 35

int main(int argc, char *argv[])
{
    int A[NN], B[NN], C[NN], i, n;
    for (i=0; i<NN; i++){ A[i]=i; B[i]=2*i; C[i]=0; }
#pragma omp parallel num_threads(4) shared(A, B, C) private(i, n)
    {
        n=omp_get_thread_num();
#pragma omp for
        for (i=0; i<NN; i++)
        {
            C[i]=A[i]+B[i];
            printf("Поток %d сложил элементы с номером %d\n",
                    n, i);
        }
    }
}
