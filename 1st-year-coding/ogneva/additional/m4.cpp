#include <iostream>
#include <cmath>
using namespace std;

struct point
{
  float x;
  float y;
};

float length(float x, float y)
{
  return sqrt(x * x + y * y);
}

int main(void)
{
  cout << "Enter number of your points: ";
  int pcount;
  cin >> pcount;

  point* pts = new point[pcount];

  
  for (int i = 0; i < pcount; i++)
  {    
    cout << "Enter your x and y: ";
    cin >> pts[i].x >> pts[i].y;
  }

  float max = 0.0;
  point res;
  for (int i = 0; i < pcount; i++)
  {
    float lng = length(pts[i] .x, pts[i].y);
    if (lng > max) {
      max = lng;
      res.x = pts[i].x;
      res.y = pts[i].y;
    }
  }
  cout << res.x << " " << res.y << endl;
  cout << max;
}