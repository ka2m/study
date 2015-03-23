#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main (void)
{
  string s;
  getline(cin, s);
  char* token;
  char delims[] = " ,-;:";
  // c_str(): string -> const char *
  // strtok(char *, char *) -> char *
  // strdup(const char *) -> char *
  token = strtok(strdup(s.c_str()), delims);  
  int maxlen = 0;
  while (token != NULL)
  {
    if (strlen(token) > maxlen)
        maxlen = strlen(token);
    cout << token << endl;
    token = strtok(NULL, delims);
  }
  cout << maxlen;
}