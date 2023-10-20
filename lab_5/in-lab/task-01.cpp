
#include <iostream>
using namespace std;

template <typename T>
class DoubleEndedQueue {
private:
  int frontIndex;
  int rearIndex;
  int queueCapacity;
  int numberOfElements;
  T *queueData;
  void resize() {
    if (queueCapacity == 0) {
      queueCapacity = 1;
      queueData = new T[queueCapacity];
    } else if (isFull()) {
      int prevQueueCapacity = queueCapacity;
      queueCapacity *= 2;
      T *temp = new T[queueCapacity];
      int j = frontIndex;
      for (size_t i = 0; i < numberOfElements; i++) {
        temp[i] = queueData[j];
        j = ++j % prevQueueCapacity;
      }
      delete[] queueData;
      queueData = temp;
      frontIndex = 0;
      rearIndex = numberOfElements - 1;
    }
  }

public:
  DoubleEndedQueue() {
    rearIndex = frontIndex = -1;
    numberOfElements = queueCapacity = 0;
    queueData = nullptr;
  }
  ~DoubleEndedQueue() {
    delete[] queueData;
    queueData = nullptr;
  }
  void insertFront(const T element) {
    this->resize();
    if (numberOfElements == 0) {
      frontIndex = 0;
      rearIndex = 0;
    } else if (frontIndex == 0) {
      frontIndex = queueCapacity - 1;
    } else {
      --frontIndex;
    }
    queueData[frontIndex] = element;
    ++numberOfElements;
  }
  void insertRear(const T element) {
    this->resize();
    if (numberOfElements == 0) {
      frontIndex = 0;
      rearIndex = 0;
    } else if (rearIndex == queueCapacity - 1) {
      rearIndex = 0;
    } else {
      ++rearIndex;
    }
    queueData[rearIndex] = element;
    ++numberOfElements;
  }
  T removeFront() {
    if (isEmpty()) {
      throw runtime_error("Exception! Removing element from empty queue!");
    } else {
      T toReturn = queueData[frontIndex];
      if (numberOfElements == 1) {
        frontIndex = -1;
        rearIndex = -1;
      } else {
        frontIndex = ++frontIndex % queueCapacity;
      }
      --numberOfElements;
      return toReturn;
    }
  }
  T removeRear() {
    if (isEmpty()) {
      throw runtime_error("Exception! Removing element from empty queue!");
    } else {
      T toReturn = queueData[rearIndex];
      if (numberOfElements == 1) {
        frontIndex = -1;
        rearIndex = -1;
      } else {
        rearIndex = (--rearIndex + queueCapacity) % queueCapacity;
      }
      --numberOfElements;
      return toReturn;
    }
  }
  bool isEmpty() const {
    return numberOfElements == 0;
  }
  bool isFull() const {
    return numberOfElements == queueCapacity;
  }
  int size() const {
    return numberOfElements;
  }
  int getCapacity() const {
    return queueCapacity;
  }
  void printQueue() {
    if (!isEmpty()) {
      int i = frontIndex;
      while (true) {
        cout << queueData[i] << " ";
        if (i == rearIndex) {
          break;
        }
        i = ++i % queueCapacity;
      }
      cout << endl;
    }
  }
};

int main() {
  DoubleEndedQueue<int> queue;

  while (true) {
    cout << "\n---------------------\nChoose an action:\n"
         << "1. Insert at front\n"
         << "2. Insert at rear\n"
         << "3. Remove from front\n"
         << "4. Remove from rear\n"
         << "5. Print queue\n"
         << "6. Exit\n";
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice == 1) {
      int element;
      cout << "Enter the element: ";
      cin >> element;
      queue.insertFront(element);
      cout << "Element inserted successfully!" << endl;
    } else if (choice == 2) {
      int element;
      cout << "Enter the element: ";
      cin >> element;
      queue.insertRear(element);
      cout << "Element inserted successfully!" << endl;
    } else if (choice == 3) {
      try {
        int removedElement = queue.removeFront();
        cout << "Element removed successfully!" << endl;
        cout << "Removed element: " << removedElement;
      } catch (exception &e) {
        cout << e.what() << endl;
      }
    } else if (choice == 4) {
      try {
        int removedElement = queue.removeRear();
        cout << "Element removed successfully!" << endl;
        cout << "Removed element: " << removedElement;
      } catch (exception &e) {
        cout << e.what() << endl;
      }
    } else if (choice == 5) {
      cout << "Queue contents: ";
      queue.printQueue();
    } else if (choice == 6) {
      return 0;
    } else {
      cout << "Invalid choice. Please try again.\n";
    }
  }

  return 0;
}