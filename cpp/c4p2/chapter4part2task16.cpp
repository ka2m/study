#include <iostream>
#include <fstream>
using namespace std;

int main(void) {
	ifstream inp("input");
	ofstream out("output");

	int num = 0;
	int t = 0;
	int i =0;
	while(inp>>num){
		cout<<num;
		t += num;
		i++;
		if (!(i%2)) {
			out<<(float)t/2<<" ";
			t = 0;
		}	
	}

	inp.close();
	out.close();
}