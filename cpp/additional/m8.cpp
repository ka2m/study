#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;


int** iter(int** a, int** b, int n)
{
  int** res = new int*[n];

  for (int i = 0; i < n; i++) {
    res[i] = new int[n];
    for (int j = 0; j<n; j++)
      res[i][j] = 0;
  }

  for (int row = 0; row < n; row++)
    for (int col = 0; col < n; col++)
      for (int inner = 0; inner < n; inner++)
        res[row][col] += a[row][inner] * b[inner][col];

  return res;
}


int** power(int** a, int** b, int n, int s)
{

  int** res = new int*[n];
  for (int i = 0; i < n; i++) {
    res[i] = new int[n];
    for (int j = 0; j < n; j++)
    res[i][j] = 0;
  }

  res = iter(a, b, n);

  if (s == 1) return res;

  for (int i = 2; i < s; i++) {
    res = iter(res, b, n);
  }

  return res;
}


int main(void)
{
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n;
  cin » n;

  int** a = new int *[n];
  int** b = new int *[n];
  int** r = new int *[n];
  for (int i = 0; i < n; i++) {
    a[i] = new int[n];
    b[i] = new int[n];
    r[i] = new int[n];
  }

  int s;
  cin >> s;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
    {
      cin >> a[i][j];
      b[i][j] = a[i][j];
      r[i][j] = 0;
    }

  r = power(a, b, n, s);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      cout << r[i][j] << " ";
    cout << endl;
    }

}