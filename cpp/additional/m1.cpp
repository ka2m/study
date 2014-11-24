#include <cmath>
#include <iostream>
using namespace std;

double f (double x, double eps, int& ncount)
{
    double step = 1;
    double s = 0;
    int fact = 3;
    int t = -1;
    while (fabs(step)>=eps)
    {
        s += step;
        step *= t*x*x/fact;
        ncount ++;
        fact += 2;
        t = -t;
    }
    return s;
}

int main (void)
{
    double eps;
    double a = 0.0;
    const double b = 1.0;
    const double h = 0.1;
    cin >> eps;
    int i = 1;
    cout << "No\t x \t F(x) \t n count\n";
    for (; a<= b; a += h)
    {
        int ncount = 0;
        double fx = f(a, eps, ncount);
        printf("%d\t%2.1f\t%4.5f\t\t%d\n", i, a, fx, ncount);
        i++;
    }
}
