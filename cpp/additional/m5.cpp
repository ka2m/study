#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct car
{
  string make;
  string regNum;
  string ownerName;
  int year;
  int km;
  bool isEarlierThan(int aYear);
  string output();
};

bool car::isEarlierThan(int aYear)
{
  return year < aYear;
}

string car::output() 
{
  ostringstream os;
  os << make << " " << regNum << " " << ownerName << " " << year << " " << km << endl;
  return os.str();
}

int main(void) 
{
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int limitYear;
  cin >> limitYear;

  vector<car> cars;
  
  car t;
  while (cin >> t.make >> t.regNum >> t.ownerName >> t.year >> t.km) 
  {
      cars.push_back(t);
  }

  for (int i = 0; i < cars.size(); i++)
  {    
    if (cars[i].isEarlierThan(limitYear))
       cout << cars[i].output();
  } 
}