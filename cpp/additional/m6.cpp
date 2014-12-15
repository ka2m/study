#include <cctype>
#include <cstdio>
#include <iostream>
using namespace std;


int main(void)
{
    freopen("input.txt", "r", stdin);
 
    string s;
  
    int max = 0;
    while (cin >> s) {
      cout << s << endl;
      int count = 0;
      for (int i = 0; i < s.size(); i++)
        if (isalpha(s[i]) || ((int) s[i] == -48 || (int) s[i] == -47)) count++;

      cout << "Current count: " << count << endl;
      if (count >= max) max = count;
    }
    cout << "Max count: " << max << endl;
}
