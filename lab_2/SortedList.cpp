#include <iostream>
using namespace std;

template <class T>
class SortedList {
  T *arr;
  int maxSize, currSize;

public:
  SortedList() {
    maxSize = 1;
    currSize = 0;
    arr = new T[maxSize];
  }
  ~SortedList() {
    delete[] arr;
    arr = nullptr;
    maxSize = 1;
    currSize = 0;
  }
  SortedList(const SortedList &obj) {
    maxSize = obj.maxSize;
    currSize = obj.currSize;
    if (maxSize == 0) {
      arr = nullptr;
    } else {
      arr = new T[maxSize];
      for (int i = 0; i < currSize; i++) {
        arr[i] = obj.arr[i];
      }
    }
  }
  const SortedList &operator=(const SortedList &obj) {
    if (this != &obj) {
      maxSize = obj.maxSize;
      currSize = obj.currSize;
      if (maxSize == 0) {
        arr = nullptr;
      } else {
        arr = new T[maxSize];
        for (int i = 0; i < currSize; i++) {
          arr[i] = obj.arr[i];
        }
      }
    }
    return *this;
  }
  bool isFull() const {
    return currSize == maxSize;
  }
  bool isEmpty() const {
    return currSize == 0;
  }
  void display() const {
    for (int i = 0; i < currSize; i++) {
      cout << arr[i] << " ";
    }
    cout << endl;
  }
  void resize() {
    if (currSize == maxSize) {
      maxSize *= 2;
      T *arr2 = new T[maxSize];
      for (size_t i = 0; i < currSize; i++) {
        arr2[i] = arr[i];
      }
      delete[] arr;
      arr = arr2;
      arr2 = nullptr;
    }
  }
  void insert(T val) {
    // Calling the resize function. This function will resize ONLY if resizing is needed.
    resize();
    // If the array is empty, directly insert the element.
    if (currSize == 0) {
      arr[0] = val;
    }
    if (arr[currSize - 1] < val) {
      arr[currSize] = val;
    } else {
      for (size_t i = 0; i < currSize; i++) {
        if (arr[i] > val) {
          for (int j = currSize; j > i; --j) {
            arr[j] = arr[j - 1];
          }
          arr[i] = val;
          break;
        }
      }
    }
    ++currSize;
  }
  bool remove(int index) {
    if (index >= currSize) {
      return false;
    }
    for (size_t i = index; i < currSize; i++) {
      arr[i] = arr[i + 1];
    }
    --currSize;
    return true;
  }
};

int main() {
  SortedList<int> list;
  int option;
  do {
    cout << "______________________" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Add an element" << endl;
    cout << "2. Remove an element" << endl;
    cout << "3. Display the list" << endl;
    cout << "4. Quit" << endl;
    cout << "Enter your choice: ";
    cin >> option;

    switch (option) {
    case 1:
      int value;
      cout << "Enter the element to add: ";
      cin >> value;
      list.insert(value);
      cout << "Element added successfully." << endl;
      break;
    case 2:
      int index;
      cout << "Enter the index of the element to remove: ";
      cin >> index;
      if (list.remove(index)) {
        cout << "Element removed successfully." << endl;
      } else {
        cout << "Invalid index. Element not removed." << endl;
      }
      break;
    case 3:
      cout << "Current List: ";
      list.display();
      break;
    case 4:
      cout << "Exiting the program." << endl;
      break;
    default:
      cout << "Invalid option. Please try again." << endl;
    }
  } while (option != 4);

  return 0;
}
