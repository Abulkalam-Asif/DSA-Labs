#include <iostream>
#include <string>
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
  int n;
  do {
    cout << "Enter the value of n(> 0): ";
    cin >> n;
  } while (n <= 0);
  DoubleEndedQueue<string> queue;
  string s = "1";
  queue.insertRear(s);
  for (int i = 0; i < n; i++) {
    string temp = queue.removeFront();
    cout << temp << " ";
    queue.insertRear(temp + "0");
    queue.insertRear(temp + "1");
  }

  return 0;
}