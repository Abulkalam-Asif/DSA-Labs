#include <iostream>
using namespace std;

static int callsCount = 0;
void printRows(int n) {
  ++callsCount;
  if (n == 0) {
    return;
  }
  cout << "*";
  printRows(n - 1);
}

void printRectangle(int n) {
  ++callsCount;
  static int m = n;
  if (n == 0) {
    return;
  }
  printRows(m - n + 1);
  cout << endl;
  printRectangle(n - 1);
}

// Time: O(n) (Almost 4n complexity)
// space: O(n) (At max, n + 1 calls would be in stack)

int main() {
  printRectangle(2);
  cout << "calls count: " << callsCount << endl;

  return 0;
}