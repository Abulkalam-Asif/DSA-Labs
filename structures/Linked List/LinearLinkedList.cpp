#include <iostream>
using namespace std;

template <typename T>
class LinearLinkedList;

template <typename T>
class Node {
private:
  T val;
  Node<T>* next;
  friend class LinearLinkedList<T>;

public:
  Node() : val(T()), next(nullptr) {}
  Node(T val) : val(val), next(nullptr) {}
  ~Node() {
    if (next) {
      delete next;
      next = nullptr;
    }
  }
};

template <typename T>
class LinearLinkedList {
private:
  Node<T>* head;
  int nodesCount;

public:
  LinearLinkedList() : head(nullptr), nodesCount(0) {}
  ~LinearLinkedList() {
    delete head;
    head = nullptr;
  }
  void insert(T val) {
    Node<T>* newNode = new Node<T>(val);
    if (nodesCount == 0) {
      head = newNode;
    } else {
      Node<T>* temp = head;
      while (temp->next) {
        temp = temp->next;
      }
      temp->next = newNode;
    }
    ++nodesCount;
  }
  bool remove(T val) {
    if (!isEmpty()) {
      if (head->val == val) {  // If the value is in the first node
        if (nodesCount == 1) { // If there is only one node
          delete head;
          head = nullptr;
        } else {
          Node<T>* temp = head;
          head = temp->next;
          temp->next = nullptr;
          delete temp;
        }
        --nodesCount;
        return true;
      } else { // If the value is not in the first node
        Node<T>* temp = head;
        while (temp->next->next) {
          if (temp->next->val == val) {
            Node<T>* temp2 = temp->next;
            temp->next = temp->next->next;
            temp2->next = nullptr;
            delete temp2;
            --nodesCount;
            return true;
          }
          temp = temp->next;
        }
        if (temp->next->val == val) {
          delete temp->next;
          temp->next = nullptr;
          --nodesCount;
          return true;
        }
        return false;
      }
    } else {
      return false;
    }
  }
  bool search(T val) {
    if (!isEmpty()) {
      if (head->val == val) {
        return true;
      } else {
        Node<T>* temp = head;
        while (temp->next) {
          if (temp->next->val == val) {
            return true;
          }
          temp = temp->next;
        }
        return false;
      }
    } else {
      return false;
    }
  }

  bool isEmpty() {
    return nodesCount == 0;
  }
  void print() {
    if (!isEmpty()) {
      Node<T>* temp = head;
      while (temp) {
        cout << temp->val << " ";
        temp = temp->next;
      }
    }
  }
};

int main() {
  LinearLinkedList<int> myList;
  cout << ">---------------<\n1- Insert" << endl;
  cout << "2- Remove" << endl;
  cout << "3- Search" << endl;
  cout << "4- Print" << endl;
  cout << "else, Exit\n"
    << endl;
  cout << "Your choice: ";
  int choice;
  cin >> choice;
  cout << "-----\n";
  while (true) {
    if (choice == 1) {
      int element;
      cout << "Enter a element to insert: ";
      cin >> element;
      myList.insert(element);
      cout << "Element inserted successfully!" << endl;
    } else if (choice == 2) {
      int element;
      cout << "Enter a element to delete: ";
      cin >> element;
      if (myList.remove(element)) {
        cout << "Element removed successfully!" << endl;
      } else {
        cout << "Element not found!" << endl;
      }
    } else if (choice == 3) {
      int element;
      cout << "Enter a element to search: ";
      cin >> element;
      if (myList.search(element)) {
        cout << "Element found!" << endl;
      } else {
        cout << "Element not found!" << endl;
      }

    } else if (choice == 4) {
      cout << "Printing the list..." << endl;
      myList.print();
    } else {
      return 0;
    }
    cout << "\n>---------------<\n1- Insert" << endl;
    cout << "2- Remove" << endl;
    cout << "3- Search" << endl;
    cout << "4- Print" << endl;
    cout << "Else, Exit" << endl;
    cout << "Your choice: ";
    cin >> choice;
    cout << "-----\n";
  }

  return 0;
}