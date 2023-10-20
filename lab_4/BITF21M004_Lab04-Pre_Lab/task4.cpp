#include <iostream>
#include <string>
using namespace std;

// Time: O(n)
// Space: O(n)

string reverse(string str, int len) {
  if (len == 0) {
    return "";
  }
  return str[len - 1] + reverse(str, len - 1);
}

int main() {
  string str;
  cout << "Enter a string: ";
  getline(cin, str);

  string reversed = reverse(str, str.size());
  cout << reversed;

  return 0;
}