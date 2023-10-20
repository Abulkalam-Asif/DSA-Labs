#include <iostream>
using namespace std;

// Time: O(n)
//  Space: O(n)

int search(int *arr, int element, int array_size) {
  static int index = -1;
  ++index;
  if (*arr == element) {
    return index;
  }
  if (*arr == arr[array_size - 1]) {
    return -1;
  }
  return search(arr + 1, element, array_size - 1);
}

int main() {
  int size;
  cout << "Enter the size of the array: ";
  cin >> size;
  int *arr = new int[size];
  cout << "Enter the elements of the array: ";
  for (int i = 0; i < size; ++i) {
    cin >> arr[i];
  }
  int element;
  cout << "Enter the element to be searched: ";
  cin >> element;
  int index = search(arr, element, size);
  if (index == -1) {
    cout << "Element not found in the array." << endl;
  } else {
    cout << "Element found at index " << index << "." << endl;
  }

  delete[] arr;
  arr = nullptr;

  return 0;
}