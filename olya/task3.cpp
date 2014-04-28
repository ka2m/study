#include <cstdio>
#include <iostream>
using namespace std;

struct occurance {
	char c = '\0'; //pre-defined values to avoid null pointers
	int pos = -1; //same here
};

void func(const char* str, char marker, occurance& oc1, occurance& oc2) {	
	int size = 0;
	for (; str[size] != marker && str[size] != '\0'; size++); //length string instead of strlen or for the marker	
	
	//two loops are cheaper than one here
	for (int i = 0; i < size-1; i++) {
		//check
		if (str[i]==str[i+1]) {
			oc1.c = str[i]; //the item
			oc1.pos = i; //its position
		}
	}

	for (int i = 0; i < size-1; i++) {
		//also check that it is not the same position!
		if (str[i]==str[i+1] && i != oc1.pos && i+1 != oc1.pos+1) {
			oc2.c = str[i];
			oc2.pos = i;
		}
	}
}

int main(void){
	string s;
	cout<<"Enter input string: ";
	cin>>s;
	getchar();
	char marker;
	cout<<"Enter EOL char: ";
	marker = getchar();

	//our results
	occurance res1, res2;
	//checking
	func(s.c_str(), marker, res1, res2);	
	//check if any doubleled chars and print them
	if (res1.pos != -1 || res2.pos != -1)
		cout<<"Doubled: "<<endl;
	else 
		cout<<"No doubled chars!"<<endl;
	if (res1.pos != -1)
		printf("\'%c\' @ %d\n", res1.c, res1.pos);
	if (res2.pos != -1)
		printf("\'%c\' @ %d\n", res2.c, res2.pos);

	
}
