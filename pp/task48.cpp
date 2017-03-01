#include <iostream>
#include <sys/time.h>
#define N 2048
double a[N][N], b[N][N], c[N][N];
using namespace std;
int main()
{
    struct timeval t1, t2;
    int i, j, k;
    for (i=0; i<N; i++)
        for (j=0; j<N; j++)
            a[i][j]=b[i][j]=i*j;
     gettimeofday(&t1, NULL);

#pragma omp parallel for shared(a, b, c) private(i, j, k)
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            c[i][j] = 0.0;
            for(k=0; k<N; k++) c[i][j]+=a[i][k]*b[k][j];
        }
    }
    gettimeofday(&t2, NULL);
    double elapsedTime;
    elapsedTime = (t2.tv_sec - t1.tv_sec);
    cout<<"Time="<<elapsedTime<<" sec"<<endl;
}
