#include <iostream>
#include <fstream>
using namespace std;

int main(void)
{
  ifstream f("f.txt");
  ofstream g("g.txt");
  ofstream h("h.txt");

  int a;
  while(f >> a)
  {
    if (!(a % 2)) 
      g << a << " ";
    else
      h << a << " ";
  }
  
  f.close();
  g.close();
  h.close();
}