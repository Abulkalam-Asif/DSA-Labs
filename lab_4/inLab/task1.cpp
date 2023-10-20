#include <iostream>
using namespace std;

static int callsCount = 0;
int binomial(int n, int m) {
  ++callsCount;
  if (n == m || m == 0)
    return 1;
  else
    return binomial(n - 1, m) + binomial(n - 1, m - 1);
}

int main() {
  cout << "result: " << binomial(7, 5) << endl;
  cout << "Function calls: " << callsCount << endl;

  return 0;
}