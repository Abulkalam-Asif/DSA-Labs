#include <iostream>
using namespace std;

void rowMajorND(int dimensions) {
  for (int i = 1; i <= dimensions; ++i) {
    cout << "i" << i;
    for (int j = i + 1; j <= dimensions; j++) {
      cout << " D" << j;
    }
    if (i != dimensions) {
      cout << " + ";
    }
  }
}

int main() {
  int dimensions;
  cout << "Enter number of dimensions: ";
  cin >> dimensions;

  rowMajorND(dimensions);

  return 0;
}