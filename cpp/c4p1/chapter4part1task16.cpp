#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
using namespace std;

int main(void) {
	ifstream ifs;
	ofstream ofs;
	ifs.open("input");
	ofs.open("output");
	string t;
	while (getline(ifs, t))
		ofs<<t<<" "<<t.length()<<"\n";

	ifs.close();
	ofs.close();
	
}