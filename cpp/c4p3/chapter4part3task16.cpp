#include <iostream>
#include <fstream>
using namespace std;

int main(void) {
	ofstream ofs("output", ios::out | ios::binary);
	int n; 
	cout<<"Enter n: ";
	cin>>n;

	for (int i=1;i<=n;i++) {
		int num = i*i;
		ofs.write(reinterpret_cast<const char *>(&num), sizeof(num));
	}

	ofs.close();
	ifstream ifs("output", ios::in | ios::binary);

	ifs.seekg (0, ifs.end);
    int length = ifs.tellg();
    ifs.seekg (0, ifs.beg);
    int pos = ifs.tellg();
	int num;
	 while(pos<length) {
		ifs.read((char*)&num, sizeof(int));
		pos+=2*sizeof(int);
		ifs.seekg(pos);
		cout<<num<<endl;		
	}
}