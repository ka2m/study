#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void print(vector<int>& v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		cout<<*it<<" ";	
	cout<<endl;
}

int main() {
	freopen("input","r",stdin);
	freopen("output","w",stdout);
	vector<int> vec;
	int k, t;
	
	cin >> k;
	while(cin>>t) vec.push_back(t);

	print(vec);

	int size = vec.size();

	for (int i=k; i<= size; i+= k) {		
		vec.insert(vec.begin()+i, -1);
		i++;
	}

	print(vec);
}