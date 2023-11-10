#include <iostream>
using namespace std;

// Forward Declaration
template <typename T>
class DoublyLinearLinkedList;

template <typename T>
class Node {
  friend class DoublyLinearLinkedList<T>;

private:
  T data;
  Node<T> *prev;
  Node<T> *next;

public:
  Node() : data(T()), prev(nullptr), next(nullptr) {}
  Node(T data) : data(data), prev(nullptr), next(nullptr) {}
  ~Node() {
    if (prev) {
      delete prev;
      prev = nullptr;
    }
    if (next) {
      delete next;
      next = nullptr;
    }
  }
};

template <typename T>
class DoublyLinearLinkedList {
private:
  Node<T> *head;
  Node<T> *tail;
  int nodesCount;

public:
  DoublyLinearLinkedList() : head(nullptr), tail(nullptr) : nodesCount(0) {}

  DoublyLinearLinkedList(const DoublyLinearLinkedList<T> &obj) { // O(n)
    if (obj.head == nullptr) {
      head = nullptr;
      tail = nullptr;
      nodesCount = 0;
    } else {
      head = new Node<T>(obj.head->data);
      nodesCount = 1;
      if (obj.head->next == nullptr) { // If there is only one node
        tail = head;
      } else { // If there are more than one nodes
        Node<T> *tempThis = head;
        Node<T> *tempObj = obj.head;
        while (tempObj != obj.tail) {
          tempThis->next = new Node<T>(tempObj->next->data);
          tempThis->next->prev = tempThis;
          tempThis = tempThis->next;
          tempObj = tempObj->next;
          ++nodesCount;
        }
        tail = tempThis;
      }
    }
  }

  void insertAtHead(T value) { // O(1)
    if (head == nullptr) {     // If there is not any node
      head = new Node<T>(value);
      tail = head;
    } else { // If there is/are already some node(s)
      Node<T> *temp = head;
      head = new Node<T>(value);
      head->next = temp;
      temp->prev = head;
    }
    ++nodesCount;
  }

  void insertAtTail(T value) { // O(1)
    if (head == nullptr) {     // If there is not any node
      tail = new Node<T>(value);
      head = tail;
    } else { // If there is/are already some node(s)
      Node<T> *temp = tail;
      tail = new Node<T>(value);
      tail->prev = temp;
      temp->next = tail;
    }
    ++nodesCount;
  }

  bool deleteAtHead() {   // O(1)
    if (head) {           // If there is at least one node
      if (head == tail) { // If there is exactly one node
        delete head;
        head = nullptr;
        tail = nullptr;
      } else { // If there are more than one nodes
        head = head->next;
        head->prev->next = nullptr;
        delete head->prev;
        head->prev = nullptr;
      }
      --nodesCount;
      return true;
    }
    return false;
  }

  bool deleteAtTail() {   // O(1)
    if (head) {           // If there is at least one node
      if (head == tail) { // If there is exactly one node
        delete tail;
        tail = nullptr;
        head = nullptr;
      } else { // If there are more than one nodes
        tail = tail->prev;
        tail->next->prev = nullptr;
        delete tail->next;
        tail->next = nullptr;
      }
      --nodesCount;
      return true;
    }
    return false;
  }

  void printList() { // O(n)
    if (head) {
      Node<T> *temp = head;
      while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
      }
    }
  }
};

int main() {
  DoublyLinearLinkedList<int> myList;
  cout << "\n>---------------<\n";
  cout << "1- Insert at head" << endl;
  cout << "2- Insert at tail" << endl;
  cout << "3- Delete at head" << endl;
  cout << "4- Delete at tail" << endl;
  cout << "5- Test copy constructor" << endl;
  cout << "6- Print" << endl;
  cout << "7- Exit" << endl;
  cout << "\nYour choice: ";
  int choice;
  cin >> choice;
  cout << "-----\n";
  while (choice != 7) {
    if (choice == 1) {
      int element;
      cout << "Enter an element to insert at head: ";
      cin >> element;
      myList.insertAtHead(element);
      cout << "Element inserted at head successfully!";
    } else if (choice == 2) {
      int element;
      cout << "Enter an element to insert at tail: ";
      cin >> element;
      myList.insertAtTail(element);
      cout << "Element inserted at tail successfully!";
    } else if (choice == 3) {
      if (myList.deleteAtHead()) {
        cout << "Element deleted at head successfully!";
      } else {
        cout << "Could not delete an element from empty list";
      }
    } else if (choice == 4) {
      if (myList.deleteAtTail()) {
        cout << "Element deleted at tail successfully!";
      } else {
        cout << "Could not delete an element from empty list";
      }
    } else if (choice == 5) {
      DoublyLinearLinkedList<int> myList2(myList);
      cout << "Original List: ";
      myList.printList();
      cout << "\nCopied List: ";
      myList2.printList();
    } else if (choice == 6) {
      cout << "List: ";
      myList.printList();
    } else {
      cout << "Invalid choice! Try again.";
    }
    cout << "\n\n>---------------<\n";
    cout << "1- Insert at head" << endl;
    cout << "2- Insert at tail" << endl;
    cout << "3- Delete at head" << endl;
    cout << "4- Delete at tail" << endl;
    cout << "5- Test copy constructor" << endl;
    cout << "6- Print" << endl;
    cout << "7- Exit" << endl;
    cout << "\nYour choice: ";
    cin >> choice;
    cout << "-----\n";
  }

  return 0;
}