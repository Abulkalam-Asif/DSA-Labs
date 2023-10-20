#include <iostream>
using namespace std;

void printMaze(int **result, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << result[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

static bool isReached = false;
bool findPath(int **maze, int **result, int rows, int cols, int Sx, int Sy, int Dx, int Dy) {
  if (maze[Sx][Sy] == 2) {
    return false;
  }
  if (maze[Sx][Sy] == 0) {
    result[Sx][Sy] = 1;
    maze[Sx][Sy] = 2;
  }
  if (maze[Sx][Sy] == 1) {
    return false;
  }
  if (Sx == Dx && Sy == Dy) {
    isReached = true;
    return true;
  }

  if (Sx >= 0 && Sx < rows - 1) {
    findPath(maze, result, rows, cols, Sx + 1, Sy, Dx, Dy);
  }

  if (Sy >= 0 && Sy < cols - 1) {
    findPath(maze, result, rows, cols, Sx, Sy + 1, Dx, Dy);
  }

  if (Sx > 0 && Sx <= rows - 1) {
    findPath(maze, result, rows, cols, Sx - 1, Sy, Dx, Dy);
  }

  if (Sy > 0 && Sy <= cols - 1) {
    findPath(maze, result, rows, cols, Sx, Sy - 1, Dx, Dy);
  }

  return isReached;
}

int main() {
  int rows, cols;
  cout << "Enter number of rows and columns: ";
  cin >> rows >> cols;
  int **maze = new int *[rows];
  int **result = new int *[rows];
  for (int i = 0; i < rows; i++) {
    maze[i] = new int[cols];
    result[i] = new int[cols]{0};
  }

  cout << "Enter values for maze (0 for open cell, 1 for blocked cell):\n";
  for (int i = 0; i < rows; i++) {
    cout << "Enter row " << i << ": ";
    for (int j = 0; j < cols; j++) {
      cin >> maze[i][j];
      while (maze[i][j] != 1 && maze[i][j] != 0) {
        cout << "Enter only 1 or 0!\n";
        cin >> maze[i][j];
      }
    }
  }
  int Sx, Sy, Dx, Dy;
  cout << "Enter row and column index for source cell: ";
  cin >> Sx >> Sy;
  while (maze[Sx][Sy] == 1 || Sx < 0 || Sy < 0 || Sx >= rows || Sy >= cols) {
    cout << "Invalid source index. Try again.";
    cin >> Sx >> Sy;
  }

  cout << "Enter row and column index for destination cell: ";
  cin >> Dx >> Dy;
  while (maze[Dx][Dy] == 1 || Dx < 0 || Dy < 0 || Dx >= rows || Dy >= cols) {
    cout << "Invalid destination index. Try again.";
    cin >> Dx >> Dy;
  }

  int isFound = findPath(maze, result, rows, cols, Sx, Sy, Dx, Dy);
  if (isFound) {
    cout << "\nPath found!\n\n";
  } else {
    cout << "\nPath not found!\n\n";
  }
  printMaze(result, rows, cols);

  return 0;
}

// I have tried to handle the user input but please give valid input.
// SAMPLE INPUT (Just uncomment it, copy it, comment it back, run the program and paste it there)

// 6 4
// 0 0 1 1
// 1 0 1 0
// 1 0 1 1
// 1 0 0 0
// 0 0 0 0
// 0 0 0 0
// 0 0
// 5 3