#include <iostream>
#include <fstream>
using namespace std;

int** power(int** a, int** b, int n, int s)
{
  int **res = new int *[n];

  for (int i = 0; i < n; i++)
    res[i]=new int[n];

  for (int i=0;i<n;i++)
    for (int j=0;j<n;j++)
      res[i][j] = 0;

  for ( int m = 1; m < s; m++)
    for (int row = 0; row < n; row++)
      for (int col = 0; col < n; col++)
        for (int inner = 0; inner < n; inner++)
          res[row][col] += a[row][inner] * b[inner][col];

  return res;
}

int main (void)
{

  ifstream in ("input.txt");
  ofstream out ("output.txt");
  
  int n;
  in >> n;
  
  int **a= new int *[n];
  int **b= new int *[n];

  for (int i = 0; i < n; i++) {
    a[i]=new int[n];
    b[i]=new int[n];
  }
  
  int s;
  in >> s;
  for ( int i = 0; i < n; i++)
    for ( int j = 0; j < n; j++)
      {
        in >> a[i][j];
        b[i][j] = a[i][j];
      }

  int **r = power(a,b, n, s);
  
  for ( int i = 0; i < n; i++) {
    for ( int j = 0; j < n; j++)
      out << r[i][j] << " ";
    out << endl;
  }
}