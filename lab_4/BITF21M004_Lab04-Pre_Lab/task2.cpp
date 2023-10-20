#include <iostream>
using namespace std;

// Time: O(n)
// Space: O(n)

int pow(int number, int power) {
  if (power == 0) {
    return 1;
  }
  if (power == 1) {
    return number;
  }
  return number * pow(number, power - 1);
}

int main() {
  int base, power;
  cout << "Enter the base: ";
  cin >> base;
  cout << "Enter the power (non-negative integer): ";
  cin >> power;
  int result = pow(base, power);
  cout << base << " raised to the power of " << power << " is: " << result << endl;

  return 0;
}