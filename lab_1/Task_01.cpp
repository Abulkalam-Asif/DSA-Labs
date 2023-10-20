#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
#define SIZE 1000

int fnLinearSearch(int array[], unsigned int size, int searchKey) {
  for (size_t i = 0; i < size; i++) {
    if (array[i] == searchKey) {
      return i;
    }
  }
  return -1;
}

int fnBinarySearch(int array[], unsigned int size, int searchKey) {
  int start = 0, end = size - 1;
  while (start < (end - 1)) {
    int mid = (end - start) / 2;
    if (searchKey == array[mid]) {
      return mid;
    } else if (searchKey < array[mid]) {
      end = mid;
    } else {
      start = mid;
    }
  }
  return -1;
}

void fnBubbleSort(int array[], unsigned int size, int sortKey) {
  int temp = 0;  // 1
  if (sortKey) { // 1
    // Descending order
    for (size_t i = 0; i < size - 1; i++) { // 1 + size + (size - 1)
      for (size_t j = i + 1; j < size; j++) {
        if (array[i] < array[j]) {
          temp = array[i];
          array[i] = array[j];
          array[j] = temp;
        }
      }
    }
  } else {
    // Ascending order
    for (size_t i = 0; i < size - 1; i++) {
      for (size_t j = i + 1; j < size; j++) {
        if (array[i] > array[j]) {
          temp = array[i];
          array[i] = array[j];
          array[j] = temp;
        }
      }
    }
  }
}

// void fnSelectionSort(int Array[], unsigned int Size, int SortKey) {
// }

void printArr(int size, int arr[]) {
  for (size_t i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

int main() {
  srand(time(NULL));

  int testArr[SIZE];
  int randomNum;
  for (size_t i = 0; i < SIZE; i++) {
    randomNum = rand() % SIZE;
    testArr[i] = randomNum;
  }

  int searchKey = rand() % SIZE;

  auto start_time = chrono::high_resolution_clock::now();

  fnBubbleSort(testArr, SIZE, 0);

  // printArr(SIZE, testArr);

  // int linearInd = fnLinearSearch(testArr, SIZE, searchKey);
  // cout << "key: " << searchKey << "\tLinear index: " << linearInd << endl;

  // int binaryInd = fnBinarySearch(testArr, SIZE, searchKey);
  // cout << "key: " << searchKey << "\tBinary index: " << binaryInd << endl;

  auto end_time = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end_time -
                                                              start_time);
  std::cout << "Time taken by function: " << duration.count() << " microseconds " << std::endl;

  return 0;
}