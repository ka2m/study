#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <sys/time.h>
#include <math.h>

#define N 1000

double f(double x, double y, double z)
{
    return sin(x * x + y * y + z * z) / (2 + cos(x - y * y + z));
}

int main(int argc, char *argv[])
{
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    double A = 0.0;
    double h = 1.0/N;
    int i,j,k;
#pragma omp parallel for reduction (+:A)
//#pragma omp parallel for reduction (+:A) schedule(static)
//#pragma omp parallel for reduction (+:A) schedule(dynamic)
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++) {
                for (k=0; k<N; k++) {
                    double itm = f(h*(i + 0.5),
                           h*(j + 0.5),
                           h*(k + 0.5));
                    A += itm;
                }
            }
        }

    gettimeofday(&t2, NULL);
    double elapsedTime;
    elapsedTime = (t2.tv_sec - t1.tv_sec);
    std::cout<<"Time="<<elapsedTime<<" sec"<<std::endl;
    std::cout<<"Result="<<(1.0/N)*(1.0/N)*(1.0/N)*A<<std::endl;
}
