#include <climits>
#include <iostream>
using namespace std;

int subarrayKadane(int *arr, int size) {
  // Start of the algorithm
  int maxSum = INT_MIN, currentMax = 0;
  for (size_t i = 0; i < size; i++) {
    currentMax += arr[i];
    if (maxSum < currentMax) {
      maxSum = currentMax;
    }
    if (currentMax < 0) {
      currentMax = 0;
    }
  }
  return maxSum;
  // End of the algorithm
}

int main() {
  // Here we are taking input from the user into two **DYNAMICALLY ALLOCATED** arrays
  int size = 0;
  cout << "Enter the size of the array: ";
  cin >> size;
  int *arr = new int[size];
  cout << "Enter elements of the array: ";
  for (size_t i = 0; i < size; i++) {
    cin >> arr[i];
  }

  // Function Call
  int maxSum = subarrayKadane(arr, size);
  cout << "Maximum sum of subarray is: " << maxSum << endl;

  return 0;
}