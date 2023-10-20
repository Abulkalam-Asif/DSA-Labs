#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void allocateArray(int ***arr, int n = 3) {
  for (int i = 0; i < n; i++) {
    *(arr + i) = new int *[n];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      *(*(arr + i) + j) = new int[n];
    }
  }
}
void initializeArray(int ***arr, int n = 3) {
  srand(time(NULL));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        *(*(*(arr + i) + j) + k) = rand() % 50;
      }
    }
  }
}
void printArray(int ***arr, int n = 3) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        cout << *(*(*(arr + i) + j) + k) << " ";
      }
      cout << endl;
    }
    cout << endl
         << endl;
  }
}

void deallocateArray(int ***arr, int n = 3) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      delete[] *(*(arr + i) + j);
    }
  }
  for (int i = 0; i < n; i++) {
    delete[] *(arr + i);
  }
  delete[] arr;
  arr = nullptr;
}

int main() {
  int ***arr = nullptr;
  arr = new int **[4];
  allocateArray(arr, 4);
  initializeArray(arr, 4);
  printArray(arr, 4);
  deallocateArray(arr, 4);

  return 0;
}