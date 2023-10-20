#include <fstream>
#include <iostream>
using namespace std;

class Matrix {
private:
  int **data;
  int rows;
  int cols;

public:
  Matrix(int numRows = 0, int numCols = 0) {
    rows = numRows;
    cols = numCols;
    if (numRows > 0 && numCols > 0) {
      data = new int *[numRows];
      for (size_t i = 0; i < numRows; i++) {
        data[i] = new int[numCols]{0};
      }
    } else {
      data = nullptr;
    }
  }
  ~Matrix() {
    for (size_t i = 0; i < rows; i++) {
      delete[] data[i];
    }
    delete[] data;
    data = nullptr;
    rows = 0;
    cols = 0;
  }

  void setValue(int row, int col, int value) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
      data[row][col] = value;
    }
  }
  int getValue(int row, int col) const {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
      return data[row][col];
    } else {
      throw runtime_error("Index out of range");
    }
  }
  void display() const {
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        cout << data[i][j] << " ";
      }
      cout << endl;
    }
  }
  int *operator[](int row) {
    if (row >= 0 && row < rows) {
      return data[row];
    }
  }
};

class SparseMatrix {
private:
  int nonZero;
  const int sparseCols;
  int **sparseMat;

public:
  SparseMatrix() : sparseCols(3), nonZero(0) {}
  void readSparseMatrix(ifstream &file) {
    Matrix mat1(10, 10);
    if (file.is_open()) {
      int num;
      for (size_t i = 0; i < 10 || !file.eof(); i++) {
        for (size_t j = 0; j < 10; j++) {
          file >> num;
          mat1.setValue(i, j, num);
          if (num != 0) {
            ++nonZero;
          }
        }
      }
    }
    file.close();
    sparseMat = new int *[nonZero];
    for (size_t i = 0; i < nonZero; i++) {
      sparseMat[i] = new int[sparseCols];
    }
    int k = 0;
    for (size_t i = 0; i < 10; i++) {
      for (size_t j = 0; j < 10; j++) {
        if (mat1[i][j] != 0) {
          sparseMat[k][0] = mat1[i][j];
          sparseMat[k][1] = i;
          sparseMat[k][2] = j;
          ++k;
        }
      }
    }
  }
  void displaySparseMatrix() {
    int k = 0;
    for (size_t i = 0; i < 10; i++) {
      for (size_t j = 0; j < 10; j++) {
        if (sparseMat[k][1] == i && sparseMat[k][2] == j) {
          cout << sparseMat[k][0] << " ";
          ++k;
        } else {
          cout << "0 ";
        }
      }
      cout << endl;
    }
    cout << endl;
  }
};

int main() {
  SparseMatrix sparseMat, sparseMat2;
  ifstream file;
  file.open("file.txt");
  sparseMat.readSparseMatrix(file);
  sparseMat.displaySparseMatrix();

  ifstream file2;
  file2.open("file2.txt");
  sparseMat2.readSparseMatrix(file2);
  sparseMat2.displaySparseMatrix();

  return 0;
}