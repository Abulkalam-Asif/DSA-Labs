
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

public:
  DoubleEndedQueue() {
    rearIndex = frontIndex = -1;
    numberOfElements = queueCapacity = 0;
    queueData = nullptr;
  }
  DoubleEndedQueue(int queueCapacity) : queueCapacity(queueCapacity) {
    rearIndex = frontIndex = -1;
    numberOfElements = 0;
    if (queueCapacity > 0) {
      queueData = new T[queueCapacity];
    } else {
      queueData = nullptr;
    }
  }
  ~DoubleEndedQueue() {
    delete[] queueData;
    queueData = nullptr;
  }
  void insertFront(const T element) {
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
  bool serach(T key) {
    int i = frontIndex;
    while (true) {
      if (queueData[i] == key) {
        return true;
      }
      if (i == rearIndex) {
        break;
      }
      i = ++i % queueCapacity;
    }
    return false;
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
  int hits = 0, faults = 0;
  int memorySpace = 0;
  do {
    cout << "Enter memory space (> 0): ";
    cin >> memorySpace;
  } while (memorySpace < 1);
  int pageNumber = -1;
  DoubleEndedQueue<int> queue(memorySpace);
  while ((true)) {
    cout << "Enter page number (-1 to exit): ";
    cin >> pageNumber;
    if (pageNumber == -1) {
      break;
    }
    if (queue.serach(pageNumber)) {
      ++hits;
      cout << "hit!!!" << endl;
    } else if (queue.isFull()) {
      queue.removeFront();
      queue.insertRear(pageNumber);
      ++faults;
      cout << "fault!!!" << endl;
    } else {
      queue.insertRear(pageNumber);
    }
    queue.printQueue();
  }
  cout << "\nHits: " << hits << endl;
  cout << "Faults: " << faults << endl;

  return 0;
}