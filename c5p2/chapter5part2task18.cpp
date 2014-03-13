#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct student{
	string name;
	string faculty;
	int year;
	string group;
	int marks[5];
};

bool hasFmark(student s){
	for (int i=0;i<5;i++)
		if (s.marks[i]==2)
			return true;
	return false;
}

int main (void) {
	freopen("input","r",stdin);
	freopen("output","w",stdout);

	vector<student> vec;
	student t;
	while(cin>>t.name>>t.faculty>>t.year>>t.group>>t.marks[0]>>t.marks[1]>>t.marks[2]>>t.marks[3]>>t.marks[4])
		vec.push_back(t);

	vector<student>::iterator it;

	for (it = vec.begin();it!=vec.end();++it) {
		if (hasFmark(*it)){
			cout<<it->name<<" "<<it->faculty<<" "<<it->year<<" "<<it->group<<endl;
		}
	}
}