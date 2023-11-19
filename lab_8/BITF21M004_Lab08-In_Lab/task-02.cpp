#include <iostream>
using namespace std;

// Forward Declaration
template <typename T>
class DoublyCircularLinkedList;

template <typename T>
class Node {
  friend class DoublyCircularLinkedList<T>;

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
  // For the sake of printing a node
  friend ostream &operator<<(ostream &o, const Node<T> *obj) {
    o << obj->data;
    return o;
  }
};

template <typename T>
class DoublyCircularLinkedList {
private:
  Node<T> *head;
  int nodesCount;

public:
  DoublyCircularLinkedList() : nodesCount(0), head(nullptr) {}

  void insertAtHead(T value) { // O(1)
    insertAtTail(value);
    head = head->prev;
  }

  void insertAtTail(T value) { // O(1)
    if (nodesCount == 0) {     // If there is not any node
      head = new Node<T>(value);
      head->next = head;
      head->prev = head;
    } else {
      Node<T> *newNode = new Node<T>(value);
      newNode->next = head;
      newNode->prev = head->prev;
      newNode->prev->next = newNode;
      head->prev = newNode;
    }
    ++nodesCount;
  }

  void display() { // O(n)
    if (nodesCount != 0) {
      Node<T> *temp = head;
      while (temp->next != head) {
        cout << temp->data << " ";
        temp = temp->next;
      }
      cout << temp->data << " "; // For the last node
    }
  }

  int countNodes() {
    return nodesCount;
  }

  void combine(DoublyCircularLinkedList &list1, DoublyCircularLinkedList &list2) {
    if (list1.nodesCount == 0 && list2.nodesCount == 0) {
      return;
    } else if (list1.nodesCount == 0) {
      this->head = list2.head;
      this->nodesCount = list2.nodesCount;
    } else if (list2.nodesCount == 0) {
      this->head = list1.head;
      this->nodesCount = list1.nodesCount;
    } else {
      this->head = list1.head;
      this->head->prev->next = list2.head;
      list2.head->prev->next = this->head;
      Node<T> *temp = this->head->prev;
      this->head->prev = list2.head->prev;
      list2.head->prev = temp;
      this->nodesCount = list1.nodesCount + list2.nodesCount;

      list1.head = nullptr;
      list2.head = nullptr;
    }
  }
};

int main() {
  DoublyCircularLinkedList<int> myList;
  cout << "\n>---------------<\n";
  cout << "1- Insert at head" << endl;
  cout << "2- Insert at tail" << endl;
  cout << "3- Display the list" << endl;
  cout << "4- Combine lists" << endl;
  cout << "5- Exit" << endl;
  cout << "\nYour choice: ";
  int choice;
  cin >> choice;
  cout << "-----\n";
  while (choice != 5) {
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
      cout << "List: ";
      myList.display();
    } else if (choice == 4) {
      DoublyCircularLinkedList<int> list1, list2, list3;
      int element = 0;
      cout << "Enter elements of list 1 (-1 to exit): ";
      cin >> element;
      while (element != -1) {
        list1.insertAtTail(element);
        cin >> element;
      }
      element = 0;
      cout << "Enter elements of list 2 (-1 to exit): ";
      cin >> element;
      while (element != -1) {
        list2.insertAtTail(element);
        cin >> element;
      }
      list3.combine(list1, list2);
      cout << "The combined list is: ";
      list3.display();
    } else {
      cout << "Invalid choice! Try again.";
    }

    cout << "\n\n>---------------<\n";
    cout << "1- Insert at head" << endl;
    cout << "2- Insert at tail" << endl;
    cout << "3- Display the list" << endl;
    cout << "4- Combine lists" << endl;
    cout << "5- Exit" << endl;
    cout << "\nYour choice: ";
    cin >> choice;
    cout << "-----\n";
  }

  return 0;
}