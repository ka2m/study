#include <iostream>
#include <fstream>
using namespace std;
bool same (int *array, int m, int &val)
{
        for (int i = 1; i < m; i++)
                if (array[0] != array [i])
                        return false;
        val = array[0];
        return true;                   
}

 
int main (void)
{
        ifstream inp ("input.txt");
        int n = 0;
        int m = 0;
        inp >> n >> m;
        int** array = new int* [n];
        for (int index = 0; index < n; index++)
        {
                array[index] = new int [m];
                for (int jndex = 0; jndex < m; jndex++)
                {
                        inp>>array[index][jndex];
                }
        }


        for (int i = 0 ; i< n; i++) {
                for (int j = 0; j< m; j++)
                        cout << array[i][j] << " ";
                cout << endl;
        }

        cout << endl;

        int val = 0;
        int flag = -1;
        for (int index = 0; index < n; index++)
        {              
                if (same(array[index], m, val))
                {
                       
                        for (int jdx = 0; jdx < n; jdx++)
                        {
                                if (array[0][jdx] == val)
                                {
                                        for (int idx = 0; idx < n; idx++)
                                        {
                                                if (val != array[idx][jdx])
                                                {
                                                        break;
                                                }
                                                if (idx == n-1)
                                                        flag = jdx;
                                        }      
 
                                }
                        }

            

                        for (int jndex = 0; jndex < m; jndex++)
                                array[index][jndex]=array[index+1][jndex];
                        
                        n--;
                        
                }
        }

        for (int index = 0; index < n; index++)
                for (int jndex = 0; jndex < m; jndex++)
                        if (jndex >= flag)
                                array[index][jndex] = array[index][jndex + 1];
        m--;
        
        for (int i = 0 ; i< n; i++) {
                for (int j = 0; j< m; j++)
                        cout << array[i][j] << " ";
                cout << endl;
        }
 
}