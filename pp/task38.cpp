#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <sys/time.h>
#include <unistd.h>
using namespace std;

#define NNN 15

void My_Task(int k)
{
#ifdef _OPENMP
    int n=omp_get_thread_num();
#else
    int n=0;
#endif
    printf("k= %d Поток %d начал вычисления\n", k, n);
    sleep(2);
    printf("k= %d Поток %d выполнил вычисления\n", k, n);
}

int main(int argc, char *argv[])
{
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
#pragma omp parallel
    {
#pragma omp for
        for (int k=0; k<NNN; k++){
#pragma omp task
            My_Task(k);
        }
#pragma omp taskwait

    }
    printf("Подзадачи завершены\n");
    gettimeofday(&t2, NULL);
    double elapsedTime;
    elapsedTime = (t2.tv_sec - t1.tv_sec);

    cout<<"Time="<<elapsedTime<<" sec"<<endl;
}
