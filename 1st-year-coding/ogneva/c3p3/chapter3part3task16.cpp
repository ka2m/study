#include <iostream>
#include <cstdio>
#include <string>
using namespace std;



void func(string s, int position, const char mask, string addition){
	
	if (position==s.length()) {
		cout<<s;
		return;
	}
	if (s[position]==mask)
		s.insert(position+1, addition);

	func(s,position+1, mask, addition);
}

int main(void) {
	string input_string;
	char mask;
	string addition;

	freopen("input", "r", stdin);
	freopen("output", "w", stdout);

	getline(cin, input_string);
	cin>>mask;
	cin>>addition;
	func(input_string, 0, mask, addition);
}