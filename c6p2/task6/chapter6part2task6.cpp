#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
 
void sort(vector<vector<int> >& vec) {	
	for (int k=0; k<vec.size(); k++) {
	for (int i=vec[k].size()-1; i>0; i--) {
    	for (int j=0; j<i; j++) {	  		
      		if (vec[j][k] > vec[j+1][k]) 
        		swap( vec[j][k], vec[j+1][k]);
    	}
  	}
  }
}


void print(vector<vector<int> >& v)
{
	for (int i=0;i<v.size();i++) {
		for (int j=0;j<v[i].size();j++)
			cout<<v[i][j]<<" ";
		cout<<endl;
	}
}

int main(void){
	

	freopen("input","r",stdin);
	freopen("output","w",stdout);

	int n;
	cin>>n;

	vector<vector<int> > matrix;
	for (int i=0;i<n;i++)
	{
		vector<int> t = vector<int>(n,0);
		matrix.push_back(t);
	}
	
	for (int i=0;i<n;i++) {			
		for (int j=0;j<n;j++) {			
			cin>>matrix[i][j];
		}				
	}

	print(matrix);
	cout<<"----\n";

	sort(matrix);
	
	print(matrix);

}