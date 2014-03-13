#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

struct point {
	double x;
	double y;
};

vector<point> arr;

double sq(double a){
	return a*a;
}

double lng(point a, point b) {
	return (sqrt(sq(b.x-a.x)+sq(b.y-a.y)));
}

double perimeter(point x1, point x2, point x3){
	double a = lng(x1,x2);
	double b = lng(x2,x3);
	double c = lng(x3,x1);

	return (a+b+c);
}

void printPoint(point a){
	printf(" (%4.2f;%4.2f) ",a.x,a.y);
}

bool notEqual(point a, point b){
	if ((a.x==b.x)&&(a.y==b.y))
		return false;
	return true;
}

int main(void) {
	int n;
	freopen("input","r",stdin);
	cin>>n;

	for (int i=0;i<n;i++) {
		point t;
		cin>>t.x>>t.y;
		arr.push_back(t);
	}

	double max = 0.0;
	point maxp[3];
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			for (int k=0;k<n;k++) 
				if (notEqual(arr[i],arr[j])&&notEqual(arr[j],arr[k])&&notEqual(arr[i],arr[k])) {
					printf("Perimeter with points");
					printPoint(arr[i]);
					printPoint(arr[j]);
					printPoint(arr[k]);
					printf("equals %4.2f\n-----\n", perimeter(arr[i],arr[j],arr[k]));
					if (perimeter(arr[i],arr[j],arr[k])>max) {
						max = perimeter(arr[i],arr[j],arr[k]);
						maxp[0] = arr[i];
						maxp[1] = arr[j];
						maxp[2] = arr[k];
				}
			}
	
	cout<<"Max perimeter is: "<<max<<" with points: ";
	printPoint(maxp[0]);
	printPoint(maxp[1]);
	printPoint(maxp[2]);


}
