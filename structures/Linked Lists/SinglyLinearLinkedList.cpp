#include <iostream>
using namespace std;

template <typename T>
class SinglyLinearLinkedList;

template <typename T>
class Node {
private:
  T val;
  Node<T> *next;
  friend class SinglyLinearLinkedList<T>;

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
class SinglyLinearLinkedList {
private:
  Node<T> *head;
  int nodesCount;

public:
  SinglyLinearLinkedList() : head(nullptr), nodesCount(0) {}
  SinglyLinearLinkedList(const SinglyLinearLinkedList &obj) : nodesCount(obj.nodesCount) { // O(n)
    if (obj.head == nullptr) {
      head = nullptr;
    } else if (obj.nodesCount >= 1) {
      head = new Node<T>(obj.head->val);
      if (obj.nodesCount > 1) {
        Node<T> *tempObj = obj.head;
        Node<T> *tempNew = head;
        while (tempObj->next) {
          tempNew->next = new Node<T>(tempObj->next->val);
          tempNew = tempNew->next;
          tempObj = tempObj->next;
        }
      }
    }
  }
  void insertAtHead(T val) { // O(1)
    Node<T> *temp = new Node<T>(val);
    if (nodesCount == 0) {
      head = temp;
    } else {
      temp->next = head;
      head = temp;
    }
    ++nodesCount;
  }
  void insertAtTail(T val) { // O(n)
    Node<T> *newNode = new Node<T>(val);
    if (nodesCount == 0) {
      head = newNode;
    } else {
      Node<T> *temp = head;
      while (temp->next) {
        temp = temp->next;
      }
      temp->next = newNode;
    }
    ++nodesCount;
  }
  bool deleteAtHead() { // O(1)
    if (!isEmpty()) {
      if (nodesCount == 1) {
        delete head;
        head = nullptr;
      } else {
        Node<T> *temp = head;
        head = head->next;
        temp->next = nullptr;
        delete temp;
      }
      --nodesCount;
      return true;
    }
    return false;
  }
  bool deleteAtTail() { // O(n)
    if (!isEmpty()) {
      if (nodesCount == 1) {
        delete head;
        head = nullptr;
      } else {
        Node<T> *temp = head;
        while (temp->next->next) {
          temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
      }
      --nodesCount;
      return true;
    }
    return false;
  }
  bool deleteVal(T val) { // O(n)
    if (!isEmpty()) {
      if (head->val == val) {  // If the value is in the first node
        if (nodesCount == 1) { // If there is only one node
          delete head;
          head = nullptr;
        } else {
          Node<T> *temp = head;
          head = temp->next;
          temp->next = nullptr;
          delete temp;
        }
        --nodesCount;
        return true;
      } else { // If the value is not in the first node
        Node<T> *temp = head;
        while (temp->next->next) {
          if (temp->next->val == val) {
            Node<T> *temp2 = temp->next;
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
  bool search(T val) { // O(n)
    if (!isEmpty()) {
      if (head->val == val) {
        return true;
      } else {
        Node<T> *temp = head;
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
      Node<T> *temp = head;
      while (temp) {
        cout << temp->val << " ";
        temp = temp->next;
      }
    }
  }
};

int main() {
  SinglyLinearLinkedList<int> myList;
  cout << "\n>---------------<\n";
  cout << "1- Insert at head" << endl;
  cout << "2- Insert at tail" << endl;
  cout << "3- Delete at head" << endl;
  cout << "4- Delete at tail" << endl;
  cout << "5- Delete a value" << endl;
  cout << "6- Search" << endl;
  cout << "7- Test copy constructor" << endl;
  cout << "8- Print the list" << endl;
  cout << "else, Exit\n"
       << endl;
  cout << "Your choice: ";
  int choice;
  cin >> choice;
  cout << "-----\n";
  while (true) {
    if (choice == 1) {
      int element;
      cout << "Enter a element to insert at head: ";
      cin >> element;
      myList.insertAtHead(element);
      cout << "Element inserted at head successfully!" << endl;
    } else if (choice == 2) {
      int element;
      cout << "Enter a element to insert at tail: ";
      cin >> element;
      myList.insertAtTail(element);
      cout << "Element inserted at tail successfully!" << endl;
    } else if (choice == 3) {
      if (myList.isEmpty()) {
        cout << "Could not delete an element from empty list" << endl;
      } else {
        myList.deleteAtHead();
        cout << "Element deleted at head successfully!" << endl;
      }
    } else if (choice == 4) {
      if (myList.isEmpty()) {
        cout << "Could not delete an element from empty list" << endl;
      } else {
        myList.deleteAtTail();
        cout << "Element deleted at tail successfully!" << endl;
      }
    } else if (choice == 5) {
      int element;
      cout << "Enter a element to delete: ";
      cin >> element;
      if (myList.deleteVal(element)) {
        cout << "Element removed successfully!" << endl;
      } else {
        cout << "Element not found!" << endl;
      }
    } else if (choice == 6) {
      int element;
      cout << "Enter a element to search: ";
      cin >> element;
      if (myList.search(element)) {
        cout << "Element found!" << endl;
      } else {
        cout << "Element not found!" << endl;
      }
    } else if (choice == 7) {
      SinglyLinearLinkedList<int> myList2(myList);
      cout << "Printing the new list..." << endl;
      myList2.print();
    } else if (choice == 8) {
      cout << "Printing the list..." << endl;
      myList.print();
    } else {
      return 0;
    }

    // UNCOMMENT
    cout << "Printing the list..." << endl;
    myList.print();

    cout << "\n>---------------<\n";
    cout << "1- Insert at head" << endl;
    cout << "2- Insert at tail" << endl;
    cout << "3- Delete at head" << endl;
    cout << "4- Delete at tail" << endl;
    cout << "5- Delete a value" << endl;
    cout << "6- Search" << endl;
    cout << "7- Test copy constructor" << endl;
    cout << "8- Print the list" << endl;
    cout << "else, Exit\n"
         << endl;
    cout << "Your choice: ";
    cin >> choice;
    cout << "-----\n";
  }

  return 0;
}