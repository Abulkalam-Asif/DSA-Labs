#include <iostream>
using namespace std;

// Time: O(log(n) base 10)
// Space: O(n)

int number_of_digits(int number) {
  static int count = 0;
  ++count;
  if (number < 10 && number > -10) {
    return count;
  }
  return number_of_digits(number / 10);
}

int main() {
  int number;
  cout << "Enter the number: ";
  cin >> number;
  int result = number_of_digits(number);
  cout << "The number of digits of " << number << " are: " << result << endl;

  return 0;
}