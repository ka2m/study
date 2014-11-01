#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

struct student {
	int grp;
	string lastname;
	string firstname;
	string middlename;
	int year;
	int marks[5];
};

void print(vector<student>& group){
	for(vector<student>::iterator it=group.begin();it!=group.end();++it) {
		printf("%s %s %s\n", it->lastname.c_str(), it->firstname.c_str(), it->middlename.c_str());
	}
}

bool comparator(student& a, student& b){
	if (a.lastname.compare(b.lastname)>0)
		return true;
	else 
	{
		if (a.firstname.compare(b.firstname)>0)
			return true;
		else 
		{
			if (a.middlename.compare(b.middlename)>0)
				return true;
		}
	}
	return false;
}

void sort(vector<student>& group) {
	for(int i = 1; i < group.size(); i++){
        student currElem = group[i];
        int prevKey = i - 1;
            while(prevKey >= 0 && comparator(group[prevKey], currElem)){
                group[prevKey+1] = group[prevKey];
                prevKey--; 
         }
         group[prevKey+1] = currElem;
    }
}



int main(void){
	freopen("input","r",stdin);
	freopen("output","w",stdout);
	vector<student> group;

	student t;


	while(cin>>t.grp>>t.lastname>>t.firstname>>t.middlename>>t.year>>t.marks[0]>>t.marks[1]>>t.marks[2]>>t.marks[3]>>t.marks[4]) {
		group.push_back(t);
	}
	print(group);
	sort(group);
	cout<<"\n----\n";
	print(group);
}