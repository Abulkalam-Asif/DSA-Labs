#include <iostream>
using namespace std;

// static int callsCount = 0;
int GCD(int num1, int num2, int start) {
  // ++callsCount;
  int length = num1 < num2 ? num1 : num2;
  static int i = 1;
  if (i == length)
    return i;
  else if (num1 % start == 0 && num2 % start == 0) {
    i = start;
    GCD(num1, num2, start + 1);
  }
}
// Time:
// space:

int main() {
  cout << "result: " << GCD(12, 18, 1) << endl;
  // cout << "Function calls: " << callsCount << endl;

  return 0;
}