#include <exception>
#include <iostream>
using namespace std;

template <typename T>
class DStack {
private:
  T *stack;
  int max_size;
  int curr_size;

public:
  DStack() {
    this->max_size = 0;
    curr_size = 0;
    stack = nullptr;
  }
  DStack(const DStack &obj) {
    max_size = obj.max_size;
    curr_size = obj.curr_size;
    if (max_size != 0) {
      stack = new T[max_size];
      for (size_t i = 0; i < curr_size && i < max_size; i++) {
        stack[i] = obj.stack[i];
      }
    } else {
      stack = nullptr;
    }
  }
  ~DStack() {
    delete[] stack;
    stack = nullptr;
  }
  void push(T value) {
    grow();
    stack[curr_size++] = value;
  }
  void grow() {
    if (curr_size == max_size) {
      if (max_size == 0) {
        max_size = 1;
        stack = new T[max_size];
      } else {
        DStack tempStack(*this);
        delete[] stack;
        max_size *= 2;
        stack = new T[max_size];
        for (size_t i = 0; i < tempStack.curr_size && i < this->max_size; i++) {
          stack[i] = tempStack.stack[i];
        }
      }
    }
  }
  T pop() {
    if (curr_size == 0) {
      throw std::underflow_error("Exception! Stack is empty!");
    } else {
      T popped = stack[curr_size - 1];
      shrink();
      --curr_size;
      return popped;
    }
  }
  void shrink() {
    if ((float)curr_size <= max_size / 4.0) {
      DStack tempStack(*this);
      delete[] stack;
      if (curr_size == 1) {
        max_size = 0;
        stack = nullptr;
      } else {
        max_size /= 2;
        stack = new T[max_size];
        for (size_t i = 0; i < curr_size && i < max_size; i++) {
          stack[i] = tempStack.stack[i];
        }
      }
    }
  }
  bool isEmpty() {
    if (curr_size == 0) {
      return true;
    }
    return false;
  }
  int getSize() {
    return curr_size;
  }
  int getMaxSize() {
    return max_size;
  }
  T top() {
    if (curr_size == 0) {
      throw std::underflow_error("Excpetion! Stack is empty!");
    } else {
      return stack[curr_size - 1];
    }
  }
  bool operator==(const DStack &obj) {
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
  bool operator!=(const DStack &obj) {
    if (*this == obj) {
      return false;
    }
    return true;
  }
  DStack &operator=(const DStack &obj) {
    if (*this == obj) {
      return *this;
    } else if (this->max_size == obj.max_size) {
      this->curr_size = obj.curr_size;
      for (size_t i = 0; i < obj.curr_size; i++) {
        this->stack[i] = obj.stack[i];
      }
    } else if (this->max_size != obj.max_size) {
      delete[] this->stack;
      this->max_size = obj.max_size;
      this->curr_size = obj.curr_size;
      if (max_size != 0) {
        stack = new T[max_size];
        for (size_t i = 0; i < curr_size && i < max_size; i++) {
          stack[i] = obj.stack[i];
        }
      } else {
        stack = nullptr;
      }
    }
    return *this;
  }
  friend ostream &operator<<(ostream &os, const DStack &obj) {
    for (size_t i = 0; i < obj.curr_size; ++i) {
      os << obj.stack[i] << " ";
    }
    return os;
  }
};

int main() {
  DStack<int> stack1;
  for (size_t i = 0; i < 10; i++) {
    stack1.push(i);
    cout << stack1.getSize() << " / " << stack1.getMaxSize() << endl;
  }
  cout << "Creating stack1 and displaying contents: " << stack1 << endl;
  cout << "The elemment on the top is: " << stack1.top() << endl;
  while (!stack1.isEmpty()) {
    cout << "Popped element: " << stack1.pop() << endl;
    cout << stack1.getSize() << " / " << stack1.getMaxSize() << endl;
    if (stack1.getSize() == 5)
      cout << "The elemment on the top is: " << stack1.top() << endl;
  }

  try {
    stack1.pop();
  } catch (exception &e) {
    cout << e.what() << endl;
  }
  cout << "Is stack1 empty? " << (stack1.isEmpty() ? "Yes" : "No") << endl;

  DStack<int> stack2;
  stack2.push(1);
  stack2.push(2);
  stack2.push(3);
  cout << "\nCreating stack2 and displaying contents: " << stack2 << endl;

  DStack<int> stack3(stack2);
  cout << "stack3 contents after copying from stack2: " << stack3 << endl;
  cout << "Are stack2 and stack3 equal? " << (stack2 == stack3 ? "Yes" : "No") << endl;

  stack3 = stack2;
  cout << "\nstack3 contents after assingment from stack2: " << stack3 << endl;
  cout << "stack2 contents: " << stack2 << endl;
  cout << "Are stack2 and stack3 equal? " << (stack2 == stack3 ? "Yes" : "No") << endl;
  cout << "Are stack2 and stack3 unequal? " << (stack2 != stack3 ? "Yes" : "No") << endl;

  return 0;
}