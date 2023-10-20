#include <exception>
#include <iostream>
using namespace std;

template <typename T>
class FStack {
private:
  T *stack;
  int max_size;
  int curr_size;

public:
  FStack(int max_size) {
    this->max_size = max_size;
    curr_size = 0;
    stack = new T[max_size];
  }
  FStack(const FStack &obj) {
    max_size = obj.max_size;
    curr_size = obj.curr_size;
    stack = new T[max_size];
    for (size_t i = 0; i < curr_size; i++) {
      stack[i] = obj.stack[i];
    }
  }
  ~FStack() {
    delete[] stack;
    stack = nullptr;
  }
  void push(T value) {
    if (isFull()) {
      throw std::overflow_error("Exception! Stack is full!");
    } else {
      stack[curr_size++] = value;
    }
  }
  T pop() {
    if (isEmpty()) {
      throw std::underflow_error("Exception! Stack is empty!");
    } else {
      --curr_size;
      return stack[curr_size]; // The popped element, which was on "curr_size - 1" index, is now on "curr_size" index after "curr_size" is decremented
    }
  }
  bool isEmpty() {
    if (curr_size == 0) {
      return true;
    }
    return false;
  }
  bool isFull() {
    if (curr_size == max_size) {
      return true;
    }
    return false;
  }
  int getSize() {
    return curr_size;
  }
  T &top() {
    if (curr_size == 0) {
      throw std::underflow_error("Excpetion! Stack is empty!");
    } else {
      return stack[curr_size - 1];
    }
  }
  bool operator==(const FStack &obj) {
    if (this->max_size == obj.max_size && this->curr_size == obj.curr_size) {
      for (size_t i = 0; i < this->curr_size; i++) {
        if (this->stack[i] != obj.stack[i]) {
          return false;
        }
      }
      return true;
    } else {
      return false;
    }
  }
  bool operator!=(const FStack &obj) {
    if (*this == obj) {
      return false;
    }
    return true;
  }
  FStack &operator=(const FStack &obj) {
    if (*this == obj) {
      return *this;
    } else if (this->max_size == obj.max_size) {
      this->curr_size = obj.curr_size;
      for (size_t i = 0; i < obj.curr_size; i++) {
        this->stack[i] = obj.stack[i];
      }
    } else if (this->max_size != obj.max_size) {
      delete[] this->stack;
      this->stack = nullptr;
      this->max_size = obj.max_size;
      this->curr_size = obj.curr_size;
      this->stack = new T[this->max_size];
      for (size_t i = 0; i < obj.curr_size; i++) {
        this->stack[i] = obj.stack[i];
      }
    }
    return *this;
  }
  friend ostream &operator<<(ostream &os, const FStack &obj) {
    for (size_t i = 0; i < obj.curr_size; ++i) {
      os << obj.stack[i] << " ";
    }
    return os;
  }
};

int main() {
  FStack<int> stack1(5);
  stack1.push(1);
  stack1.push(2);
  stack1.push(3);
  stack1.push(4);
  stack1.push(5);
  cout << "Creating stack1 and displaying contents: " << stack1 << endl;
  cout << "The elemment on the top is: " << stack1.top() << endl;
  cout << "Is stack1 full? " << (stack1.isFull() ? "Yes" : "No") << endl;
  try {
    stack1.push(6);
  } catch (exception &e) {
    cout << e.what() << endl;
  }
  while (!stack1.isEmpty()) {
    cout << "Popped element: " << stack1.pop() << endl;
  }
  try {
    stack1.pop();
  } catch (exception &e) {
    cout << e.what() << endl;
  }
  cout << "Is stack1 empty? " << (stack1.isEmpty() ? "Yes" : "No") << endl;

  FStack<int> stack2(8);
  stack2.push(1);
  stack2.push(2);
  stack2.push(3);
  cout << "\nCreating stack2 and displaying contents: " << stack2 << endl;

  FStack<int> stack3(stack2);
  cout << "stack3 contents after copying from stack2: " << stack3 << endl;
  cout << "Are stack2 and stack3 equal? " << (stack2 == stack3 ? "Yes" : "No") << endl;

  stack3 = stack2;
  cout << "\nstack3 contents after assingment from stack2: " << stack3 << endl;
  cout << "stack2 contents: " << stack2 << endl;
  cout << "Are stack2 and stack3 equal? " << (stack2 == stack3 ? "Yes" : "No") << endl;
  cout << "Are stack2 and stack3 unequal? " << (stack2 != stack3 ? "Yes" : "No") << endl;

  return 0;
}