#include <iostream>
using namespace std;

class TwoDArray {
private:
  int *arr;
  int rows;
  int cols;

public:
  TwoDArray() {
    rows = 0;
    cols = 0;
    arr = nullptr;
  }
  TwoDArray(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    arr = new int[rows * cols]{0};
  }
  ~TwoDArray() {
    rows = 0;
    cols = 0;
    delete[] arr;
    arr = nullptr;
  }
  TwoDArray(const TwoDArray &obj) {
    rows = obj.rows;
    cols = obj.cols;
    if (obj.rows > 0 && obj.cols > 0) {
      arr = new int[rows * cols]{0};
    }
  }
  int getIndexValue(int i, int j) {
    if (i < rows && j < cols) {
      return arr[(rows * j) + i];
    }
  }
  bool setIndexValue(int i, int j, int val) {
    if (i < rows && j < cols) {
      arr[(rows * j) + i] = val;
      return true;
    }
    return false;
  }
  void printArray() {
    for (int j = 0; j < rows; j++) {
      for (int i = 0; i <= rows * rows; i += rows) {
        cout << arr[i + j] << " ";
      }
      cout << endl;
    }
  }
  void printSubArray(int r1, int r2, int c1, int c2) {
    for (int j = c1; j < r2; j++) {
      for (int i = r1; i <= rows * rows; i += rows) {
        cout << arr[i + j] << " ";
      }
      cout << endl;
    }
  }
  int *addressOfIndex(int i, int j, int startIndex = 0) {
    if (i < rows && j < cols) {
      return (arr + (rows * j) + i + startIndex);
    }
  }
};

int main() {
  // int rows, cols;
  // cout << "Enter rows and columns of the array: ";
  // cin >> rows >> cols;
  TwoDArray arr(3, 4);
  arr.setIndexValue(0, 0, 1);
  arr.setIndexValue(0, 1, 2);
  arr.setIndexValue(0, 2, 3);
  arr.setIndexValue(1, 0, 4);
  arr.setIndexValue(1, 1, 5);
  arr.setIndexValue(1, 2, 6);
  arr.printArray();
  // arr.printSubArray(1, 2, 1, 2);
  // cout << arr.addressOfIndex(0, 1);

  return 0;
}