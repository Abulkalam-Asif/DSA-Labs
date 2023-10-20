#include <climits>
#include <iostream>
using namespace std;

template <typename T>
class Item {
  T value;
  int priority;

public:
  Item() : priority(-1), value(T()) {}
  Item(T value, int priority) : value(value), priority(priority) {}
  friend ostream& operator<<(ostream& o, const Item& obj) {
    o << obj.value << "(" << obj.priority << ")";
    return o;
  }
  T getValue() {
    return value;
  }
  int getPriority() {
    return priority;
  }
};

template <typename T>
class PriorityQueue {
private:
  int frontIndex;
  int rearIndex;
  int queueCapacity;
  int numberOfElements;
  Item<T>* queueData;

public:
  PriorityQueue() {
    rearIndex = frontIndex = -1;
    numberOfElements = queueCapacity = 0;
    queueData = nullptr;
  }
  PriorityQueue(int queueCapacity) : frontIndex(-1), rearIndex(-1), queueCapacity(queueCapacity), numberOfElements(0) {
    if (queueCapacity < 1) {
      queueData = nullptr;
    } else {
      queueData = new Item<T>[queueCapacity];
    }
  }
  PriorityQueue(const PriorityQueue& obj) : frontIndex(obj.frontIndex), rearIndex(obj.rearIndex), queueCapacity(obj.queueCapacity), numberOfElements(obj.numberOfElements) {
    if (obj.queueCapacity < 1) {
      throw runtime_error("Exception! Queue is full!");
    } else {
      queueData = new Item<T>[queueCapacity];
      for (size_t i = 0; i < numberOfElements; i++) {
        queueData[i] = obj.queueData[i];
      }
    }
  }
  ~PriorityQueue() {
    delete[] queueData;
    queueData = nullptr;
  }
  bool enqueue(Item<T>& element) {
    if (isFull()) {
      return false;
    }
    if (frontIndex == -1) {
      frontIndex = 0;
    }
    rearIndex = ++rearIndex % queueCapacity;
    queueData[rearIndex] = element;
    ++numberOfElements;
    return true;
  }
  T dequeue() {
    if (!isEmpty()) {
      T toReturn;
      if (numberOfElements == 1) {
        toReturn = queueData[frontIndex].getValue();
        frontIndex = rearIndex = -1;
      } else {
        int maxPriority = INT_MIN;
        int i = frontIndex;
        while (true) {
          if (queueData[i].getPriority() > maxPriority) {
            maxPriority = queueData[i].getPriority();
          }
          if (i == rearIndex) {
            break;
          }
          i = ++i % queueCapacity;
        }
        i = frontIndex;
        while (true) {
          if (queueData[i].getPriority() == maxPriority) {
            toReturn = queueData[i].getValue();
            int j = i;
            while (true) {
              if (j == frontIndex) {
                break;
              }
              queueData[j] = queueData[(j - 1 + queueCapacity) % queueCapacity];
              j = (--j + queueCapacity) % queueCapacity;
            }
            break;
          }
          i = ++i % queueCapacity;
        }
        frontIndex = ++frontIndex % queueCapacity;
      }
      --numberOfElements;
      return toReturn;
    } else {
      throw runtime_error("Exception! Dequeue from an empty queue!");
    }
  }
  T getFront() const {
    if (!isEmpty()) {
      T toReturn;
      if (numberOfElements == 1) {
        toReturn = queueData[frontIndex].getValue();
      } else {
        int maxPriority = INT_MIN;
        int i = frontIndex;
        while (true) {
          if (queueData[i].getPriority() > maxPriority) {
            maxPriority = queueData[i].getPriority();
          }
          if (i == rearIndex) {
            break;
          }
          i = ++i % queueCapacity;
        }
        i = frontIndex;
        while (true) {
          if (queueData[i].getPriority() == maxPriority) {
            toReturn = queueData[i].getValue();
            break;
          }
          i = ++i % queueCapacity;
        }
      }
      return toReturn;
    } else {
      throw runtime_error("Exception! Getting front from an empty queue!");
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
    if (numberOfElements != 0) {
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
  // Driver program with and integers queue
  int queueSize;
  do {
    cout << "Enter the size of queue (>= 1): ";
    cin >> queueSize;
  } while (queueSize < 1);
  PriorityQueue<int> queue(queueSize);

  while (true) {
    cout << "\n---------------------\nChoose an action:\n"
      << "1. Enqueue an element\n"
      << "2. Dequeue an element\n"
      << "3. Get the front element\n"
      << "4. Check if the queue is empty\n"
      << "5. Check if the queue is full\n"
      << "6. Get the number of elements in the queue\n"
      << "7. Get the queue capacity\n"
      << "8. Print the queue\n"
      << "9. Exit\n";

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
      if (queue.isFull()) {
        cout << "Queue is Full!" << endl;
      } else {

        int value, priority;
        cout << "Enter a value to enqueue: ";
        cin >> value;
        cout << "Enter the priority: ";
        cin >> priority;
        Item<int> queueItem(value, priority);
        queue.enqueue(queueItem);
        cout << "Element enqueued successfully!" << endl;
      }
    } else if (choice == 2) {
      try {
        int dequeuedElement = queue.dequeue();
        cout << "Element dequeued successfully!\nDequeued element: " << dequeuedElement << endl;
      } catch (exception& e) {
        cout << e.what() << endl
          << endl;
      }
    } else if (choice == 3) {
      try {
        int frontElement = queue.getFront();
        cout << "Front element: " << frontElement << endl;
      } catch (exception& e) {
        cout << e.what() << endl
          << endl;
      }
    } else if (choice == 4) {
      cout << "Is the queue empty? " << (queue.isEmpty() ? "Yes" : "No") << endl;
    } else if (choice == 5) {
      cout << "Is the queue full? " << (queue.isFull() ? "Yes" : "No") << endl;
    } else if (choice == 6) {
      cout << "Number of elements in the queue: " << queue.size() << endl;
    } else if (choice == 7) {
      cout << "Queue capacity: " << queue.getCapacity() << endl;
    } else if (choice == 8) {
      cout << "Queue contents: ";
      queue.printQueue();
    } else if (choice == 9) {
      return 0;
    }
    // else {
    //     cout << "Invalid choice. Please try again.\n";
    //   }
    // }
  }
  return 0;
}