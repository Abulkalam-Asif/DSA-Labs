#include <iostream>
using namespace std;

static int iterations = 0;

template <typename T>
bool binarySearch(T *arr, int arrSize, T key) {
  int start = 0, end = arrSize - 1;
  int mid = 0;
  while (start <= end) {
    ++iterations;
    mid = (start + end) / 2;
    if (arr[mid] == key) {
      return true;
    } else if (arr[mid] > key) {
      end = mid - 1;
    } else {
      start = mid + 1;
    }
  }
  return false;
}

int main() {
  int maxIterationsTillNow = 0;
  cout
      << "\tArray Size"
      << "\t|\t"
      << "Max Iterations" << endl;
  cout << "------------------------------------------------\n";
  for (int size = 1; size <= 1024; size++) {
    int *arr = new int[size];
    for (int i = 1; i <= size; i++) {
      arr[i] = i;
    }

    int maxIterations = 0;
    for (int i = 1; i <= size; i++) {
      bool isFound = binarySearch(arr, size, i);
      if (iterations > maxIterations) {
        maxIterations = iterations;
      }
      iterations = 0;
    }
    if (maxIterations > maxIterationsTillNow) {
      maxIterationsTillNow = maxIterations;
      cout
          << "\t" << size << "\t\t|\t" << maxIterations << endl;
    }
  }

  return 0;
}