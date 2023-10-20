#include <iostream>
#include <string>
using namespace std;

// Time: O(log(n) base 2)
// Space: O(n)

int binary_search(int *arr, int left, int right, int target) {
  int mid = (right + left) / 2;
  if (right < left) {
    return -1;
  } else if (arr[mid] == target) {
    return mid;
  } else if (arr[mid] > target) {
    return binary_search(arr, left, mid - 1, target);
  } else if (arr[mid] < target) {
    return binary_search(arr, mid + 1, right, target);
  }
}

int main() {

  int size;
  cout << "Enter the number of elements in the array: ";
  cin >> size;

  int *arr = new int[size];

  cout << "Enter the sorted elements in the array: ";
  for (int i = 0; i < size; i++) {
    cin >> arr[i];
  }

  int target;
  cout << "Enter the target element to search for: ";
  cin >> target;

  int result = binary_search(arr, 0, size - 1, target);

  if (result != -1) {
    cout << "Element " << target << " found at index: " << result << endl;
  } else {
    cout << "Element " << target << " not found in the array." << endl;
  }

  delete[] arr;
  arr = nullptr;

  return 0;
}