#include <climits>
#include <iostream>
using namespace std;

void printArray(int *arr, int start, int end) {
  for (size_t i = start; i <= end; i++) {
    cout << arr[i] << " ";
  }
}

void subarrayBruteForce(int *arr, int size) {
  int maxSum = INT_MIN;
  int maxStart = 0, maxEnd = 0;
  int currentStart = 0, currentEnd = 0;
  while (currentStart < size) {
    int currentSum = 0;
    for (size_t j = currentStart; j <= currentEnd; j++) {
      currentSum += arr[j];
    }
    if ((currentSum > maxSum) || (currentSum == maxSum && (currentEnd - currentStart < maxEnd - maxStart))) {
      maxSum = currentSum;
      maxStart = currentStart;
      maxEnd = currentEnd;
    }
    if (currentEnd == size - 1) {
      currentStart++;
      currentEnd = currentStart;
    } else
      currentEnd++;
  }

  // Printing the sub array
  cout << "Max sum is: " << maxSum << endl;
  printArray(arr, maxStart, maxEnd);
}

int subarrayKadane(int *arr, int size) {
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
  cout << "Max sum is: " << maxSum << endl;
}

int main() {
  int arr[4] = {1, 3, -2, 4};
  subarrayBruteForce(arr, 4);
  subarrayKadane(arr, 4);

  return 0;
}