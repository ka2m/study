#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

void print(vector<int>& v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		cout<<*it<<" ";	
}

int main() {
	freopen("input","r",stdin);
	freopen("output","w",stdout);
	vector<int> vec;
	int t;
	
	while(cin>>t) vec.push_back(t);

	print(vec);

	vector<int>::iterator maxIt = max_element(vec.begin(), vec.end());
	vector<int>::iterator beginIt = vec.begin();
	swap(*beginIt, *maxIt);

	cout<<endl;

	print(vec);

}