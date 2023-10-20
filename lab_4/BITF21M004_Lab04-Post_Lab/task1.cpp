#include <cmath>
#include <iostream>
using namespace std;

// With Recursion
int getMovesWithRecursion(int n, int moves) {
  if (n == 1) {
    return 1;
  }
  return 1 + (2 * getMovesWithRecursion(n - 1, moves));
}

// Without Recursion
int getMovesWithoutRecursion(int n) {
  return (pow(2, n) - 1);
}

int main() {
  int noOfPlates;
  do {
    cout << "Number of plates (>0): ";
    cin >> noOfPlates;
  } while (noOfPlates < 1);

  int movesWithRecursion = getMovesWithRecursion(noOfPlates, 1);
  int movesWithoutRecursion = getMovesWithoutRecursion(noOfPlates);
  cout << "Moves with Recursion: " << movesWithRecursion << endl;
  cout << "Moves without Recursion: " << movesWithoutRecursion << endl;

  return 0;
}