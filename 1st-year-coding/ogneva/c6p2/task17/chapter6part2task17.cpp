#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
 
using namespace std;
 
template < typename create, typename create1 >
create* CreateFun (int &n, ifstream &inp)
{
        inp >> n;
        create *mas = new create [n];
        for (int i = 0; i < n; i++)
        {
                mas[i] = new create1 [n];
                for ( int j = 0; j < n; j++)
                        inp >> mas[i][j];
        }
        return mas;
}
 
template < typename print >
void PrintFun (print *mas, int &n)
{
	for (int i = 0; i < n; i++)
     {
        for ( int j = 0; j < n; j++)
			cout << mas[i][j] << " ";
        cout << endl;
     }
        cout << endl;
}
 
 
void sort_ab (vector<int*> &a)
{
	for (int i = 0; i < a.size(); i++)
	{
		int j = i;
		while (j > 0 && *a[j] < *a[j-1])
		{
			swap (*a[j], *a[j-1]);
			j--;
		}
	}
}

void sort_un (vector<int*> &a)
{
	for (int i = 0; i < a.size(); i++)
	{
		int j = i;
		while (j > 0 && *a[j] > *a[j-1])
		{
			swap (*a[j], *a[j-1]);
			j--;
		}
	}
}
 
int main(void)
{
	ifstream inp ("input.txt");
	int n;
	int **mas = CreateFun <int*,int> (n,inp);
	PrintFun <int*> (mas,n);
 
	
    for (int k = 0; k <= n; k++) 
	{
        vector<int*> aboveDiagonal;
        vector<int*> underDiagonal;
 
        for (int i = 0; i < n; i++) 
			for (int j = 0; j < n; j++) 
			{
                if (i==j-k) aboveDiagonal.push_back(&mas[i][j]);
                if (i==j+k) underDiagonal.push_back(&mas[i][j]);
			}
        if (! (aboveDiagonal.size() == n) && ! (underDiagonal.size() == n)) 
		{
           sort_ab(aboveDiagonal);
           sort_un(underDiagonal);
        }	
    }
    PrintFun <int*> (mas,n);
}
