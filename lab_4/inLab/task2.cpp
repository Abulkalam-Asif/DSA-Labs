#include <iostream>
using namespace std;

static int callsCount = 0;
int squares_sum(int n) {
  ++callsCount;
  if (n == 1) {
    return 1;
  }
  return (n * n) + squares_sum(n - 1);
}
// Time: O(n) (Sum of squares from 1 to n)
// space: O(n) (At max, all the calls from square_sum(1) to square_sum(n) would be at a time in the stack)

int main() {
  cout << "result: " << squares_sum(3) << endl;
  cout << "Function calls: " << callsCount << endl;

  return 0;
}