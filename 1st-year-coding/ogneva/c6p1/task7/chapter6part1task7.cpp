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
	int sum;
};

void sort(vector<student>& group) {
	int step = group.size() / 2;
    while (step > 0)
    {
      for (int i = 0; i < (group.size() - step); i++)
                {
                    int j = i;
                    
                    while (j >= 0 && group[j].sum < group[j + step].sum)
                  
                    {
                        //меняем их местами
                        student temp = group[j];
                        group[j] = group[j + step];
                        group[j + step] = temp;
                        j--; 
                    }
                }
                step = step / 2;//уменьшаем шаг
            }    
}


void print(vector<student>& group){
	for(vector<student>::iterator it=group.begin();it!=group.end();++it) {
		printf("%d %s %s %s %d ", it->grp, it->lastname.c_str(), it->firstname.c_str(), it->middlename.c_str(), it->year);
		for (int j=0;j<5;j++)
			printf("%d ", it->marks[j]);
		printf("Total: %d\n", it->sum);
	}
}


int main(void){
	freopen("input","r",stdin);
	freopen("output","w",stdout);
	vector<student> group;

	student t;

	while(cin>>t.grp>>t.lastname>>t.firstname>>t.middlename>>t.year>>t.marks[0]>>t.marks[1]>>t.marks[2]>>t.marks[3]>>t.marks[4]) {
		t.sum = 0;
		for (int i=0;i<5;i++) t.sum += t.marks[i];
		group.push_back(t);
	}
	print(group);	
	sort(group);
	cout<<"\n-----\n";
	print(group);
}