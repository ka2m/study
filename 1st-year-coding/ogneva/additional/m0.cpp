#include <iostream>
#include "malloc.h"
#include <cstdio>
using namespace std;

int* insert(int* array, int& size, int position, int value)
{
  size++;
  int *result = (int *) malloc(size * sizeof(int));
  for (int i = size - 1; i > position + 1; i--) {
    result[i] = array[i-1];
  }
  result[position + 1] = value;
  for (int i = 0; i <= position; i++)
    {
      result[i] = array[i];
    }

  return result;
}

void printout(int* array, int size) {

  for (int i = 0; i < size; i++)
    cout << array[i] << " ";
  cout << endl;
}

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int size_of_array;
    scanf("%d", &size_of_array);
    int *array = (int *) malloc(size_of_array * sizeof(int));

    for (int i = 0; i < size_of_array; i++)
        scanf("%d", (array + i));

    printout(array, size_of_array);

    int max = *array;
    for (int i = 0; i < size_of_array; i++)
      {
         if (*(array + i) > max) {
           max = *(array + i);
         }
      }
    
    int max_count = 0;
    int *max_pos_array = (int *) malloc(max_count * sizeof(int));
    for (int i = 0; i < size_of_array; i++)
      {
         if (*(array + i) == max) {
           max_count++;
           max_pos_array = (int *) realloc(max_pos_array, max_count * sizeof(int));
           *(max_pos_array + max_count - 1) = i;
         }
      }

    for (int i = 1; i < max_count; i++)
      {
        *(max_pos_array+i) += i;
      }


    for (int i = 0; i < max_count; i++)
        array = insert(array, size_of_array, max_pos_array[i], -1);



    printout(array, size_of_array);

}
