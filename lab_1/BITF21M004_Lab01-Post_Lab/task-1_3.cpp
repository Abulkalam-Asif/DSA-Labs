#include <climits>
#include <iostream>
using namespace std;

void mergeSortedArrays(int *arr1, int size1, int *arr2, int size2) {
  // Start of the algorithm
  int sizeMerged = size1 + size2;
  int *arrMerged = new int[sizeMerged];
  int i = 0, j = 0, k = 0;
  while (k < sizeMerged) {
    if (j == size2 || (i < size1 && arr1[i] < arr2[j])) {
      arrMerged[k] = arr1[i];
      ++i;
    } else if (i == size1 || (j < size2 && arr1[i] >= arr2[j])) {
      arrMerged[k] = arr2[j];
      ++j;
    }
    ++k;
  }
  // End of the algorithm

  // Printing the merged array
  for (size_t i = 0; i < sizeMerged; i++) {
    cout << arrMerged[i] << " ";
  }
}

int main() {
  // Here we are taking input from the user into two **DYNAMICALLY ALLOCATED** arrays
  int size1 = 0;
  cout << "Enter the size of the array 1: ";
  cin >> size1;
  int *arr1 = new int[size1];
  cout << "Enter elements array 1 in ascending order: ";
  for (size_t i = 0; i < size1; i++) {
    cin >> arr1[i];
  }

  int size2 = 0;
  cout << "Enter the size of the array 2: ";
  cin >> size2;
  int *arr2 = new int[size2];
  cout << "Enter elements array 2 in ascending order: ";
  for (size_t i = 0; i < size2; i++) {
    cin >> arr2[i];
  }

  // Function Call
  mergeSortedArrays(arr1, size1, arr2, size2);

  return 0;
}