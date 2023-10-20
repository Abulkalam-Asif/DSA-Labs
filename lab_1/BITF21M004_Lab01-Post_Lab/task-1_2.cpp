#include <iostream>
using namespace std;

void anagramDetection(char *str1, int size1, char *str2, int size2) {
  // Start of the algorithm
  if (size1 != size2) {
    cout << "Not an anagram" << endl;
    return;
  }
  int count1[128] = {0};
  int count2[128] = {0};
  for (size_t i = 0; i < size1; i++) {
    if (str1[i] >= 65 && str1[i] <= 90) {
      ++count1[str1[i] + 32];
    } else {
      ++count1[str1[i]];
    }
  }
  for (size_t i = 0; i < size2; i++) {
    if (str2[i] >= 65 && str2[i] <= 90) {
      ++count2[str2[i] + 32];
    } else {
      ++count2[str2[i]];
    }
  }

  for (size_t i = 0; i < 128; i++) {
    bool isFound = false;
    if (count1 > 0 && count1[i] != count2[i]) {
      cout << "Not an anagram" << endl;
      return;
    }
  }
  cout << "Anagram" << endl;
  // End of the algorithm
}

int main() {
  // Here we are taking input from the user into two **DYNAMICALLY ALLOCATED** arrays
  int size1 = 0;
  cout << "Enter the size of the string 1: ";
  cin >> size1;
  char *str1 = new char[size1];
  cout << "Enter string 1: ";
  for (size_t i = 0; i < size1; i++) {
    cin >> str1[i];
  }

  int size2 = 0;
  cout << "Enter the size of the string 2: ";
  cin >> size2;
  char *str2 = new char[size2];
  cout << "Enter string 2: ";
  for (size_t i = 0; i < size2; i++) {
    cin >> str2[i];
  }

  // Function Call
  anagramDetection(str1, size1, str2, size2);

  return 0;
}