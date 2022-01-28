#include <iostream>
using namespace std;

template<typename dataType>
void swapVals(dataType& a, dataType& b)
{
  dataType temp = b;
  b = a;
  a = temp;
}

template<typename dataType, typename size_type>
void insertionSort(dataType *arr, size_type n)
{
  for(int i = 1; i < n; i++)
  {
    int j = i;
    while(j > 0 && arr[j-1] > arr[j])
    {
      swapVals(arr[j], arr[j-1]);
      j--;
    }
  }
}


int main()
{
  int arr[8] = {1,7,8,5,3,6,4,2};
  insertionSort(arr, 8);
  for(int i = 0; i < 8; i++)
  {
    cout << arr[i] << ", ";
  }
  cout << endl;
}
