#include <iostream>
using namespace std;

template <typename T>
class SinglyCircularLinkedList;

template <typename T>
class Node {
private:
  T val;
  Node<T> *next;
  friend class SinglyCircularLinkedList<T>;

public:
  Node() : val(T()), next(nullptr) {}
  Node(T val) : val(val), next(nullptr) {}

  ~Node() {
    if (next) {
      delete next;
      next = nullptr;
    }
  }

  friend ostream &operator<<(ostream &o, const Node<T> *obj) {
    o << obj->val;
    return o;
  }
};

template <typename T>
class SinglyCircularLinkedList {
private:
  Node<T> *head;
  int nodesCount;

public:
  SinglyCircularLinkedList() : head(nullptr), nodesCount(0) {}

  SinglyCircularLinkedList(const SinglyCircularLinkedList &obj) : nodesCount(obj.nodesCount) { // O(n)
    if (obj.head == nullptr) {
      head = nullptr;
    } else if (obj.nodesCount >= 1) {
      head = new Node<T>(obj.head->val);
      if (nodesCount == 1) { // If there is only one node, it will be pointing to itself
        head->next = head;
      } else {
        Node<T> *tempObj = obj.head;
        Node<T> *tempNew = head;
        while (tempObj->next != obj.head) { // Copying all the elements of the remaining list
          tempNew->next = new Node<T>(tempObj->next->val);
          tempNew = tempNew->next;
          tempObj = tempObj->next;
        }
        tempNew->next = head; // Pointing the last node to head
      }
    }
  }

  void insertAtHead(T val) { // O(n)
    Node<T> *newNode = new Node<T>(val);
    if (nodesCount == 0) {
      head = newNode;
      head->next = head;
    } else {
      Node<T> *temp = head;
      while (temp->next != head) { // Traversing to the tail
        temp = temp->next;
      }
      temp->next = newNode;
      newNode->next = head;
      head = newNode;
    }
    ++nodesCount;
  }

  void insertAtTail(T val) { // O(n)
    Node<T> *newNode = new Node<T>(val);
    if (nodesCount == 0) {
      head = newNode;
      newNode->next = head;
    } else {
      Node<T> *temp = head;
      while (temp->next != head) { // Traversing to the tail
        temp = temp->next;
      }
      newNode->next = temp->next;
      temp->next = newNode;
    }
    ++nodesCount;
  }

  bool deleteAtHead() { // O(n)
    if (nodesCount == 0) {
      return false;
    }
    if (nodesCount == 1) {
      head->next = nullptr;
      delete head;
      head = nullptr;
    } else {
      Node<T> *temp = head;
      while (temp->next != head) { // Traversing to the tail
        temp = temp->next;
      }
      temp->next = head->next; // Pointing tail to the second element
      head->next = nullptr;    // Disconnecting the first element from the second element
      delete head;             // Deleting the first element
      head = temp->next;       // Moving the head pointer to the second element
    }
    --nodesCount;
    return true;
  }

  bool deleteAtTail() { // O(n)
    if (nodesCount == 0) {
      return false;
    }
    if (nodesCount == 1) {
      head->next = nullptr;
      delete head;
      head = nullptr;
    } else {
      Node<T> *temp = head;
      while (temp->next->next != head) {
        temp = temp->next;
      }
      temp->next->next = nullptr;
      delete temp->next;
      temp->next = head;
    }
    --nodesCount;
    return true;
  }

  void print() { // O(n)
    if (nodesCount != 0) {
      Node<T> *temp = head;
      while (temp->next != head) {
        cout << temp->val << " ";
        temp = temp->next;
      }
      cout << temp->val << " "; // Printing the last element
    }
  }

  // getNode : Returns pointer to last node if n > nodesCount; else, returns pointer to nth node.
  Node<T> *getNode(int n) { // O(n)
    if (nodesCount == 0) {
      throw runtime_error("Exception! List is empty!");
    } else {
      Node<T> *temp = head;
      while (temp->next != head) {
        if (n == 0) {
          return temp;
        }
        --n;
        temp = temp->next;
      }
      return temp;
    }
  }

  bool insertAfter(T key, T value) { // O(n)
    if (nodesCount == 0) {
      return false;
    } else if (nodesCount == 1) { // If there is only one node
      if (head->val == key) {
        head->next = new Node<T>(value);
        head->next->next = head;
        ++nodesCount;
        return true;
      }
      return false;
    } else {
      Node<T> *temp = head;
      Node<T> *newNode = new Node<T>(value);
      while (temp->next != head) {
        if (temp->val == key) {
          newNode->next = temp->next;
          temp->next = newNode;
          ++nodesCount;
          return true;
        }
        temp = temp->next;
      }
      // Processing the tail node
      if (temp->val == key) {
        newNode->next = temp->next;
        temp->next = newNode;
        ++nodesCount;
        return true;
      }
      return false;
    }
  }

  bool insertBefore(T key, T value) { // O(n)
    if (nodesCount == 0) {
      return false;
    } else if (nodesCount == 1) { // If there is only one node
      if (head->val == key) {
        Node<T> *newNode = new Node<T>(value);
        newNode->next = head;
        head->next = newNode;
        head = newNode;
        ++nodesCount;
        return true;
      }
      return false;
    } else {
      Node<T> *newNode = new Node<T>(value);
      if (head->val == key) { // Inserting a node before head
        Node<T> *temp = head;
        while (temp->next != head) {
          temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
        head = newNode;
        ++nodesCount;
        return true;
      } else {
        Node<T> *temp = head->next;
        while (temp != head) {
          if (temp->next->val == key) {
            newNode->next = temp->next;
            temp->next = newNode;
            ++nodesCount;
            return true;
          }
          temp = temp->next;
        }
        return false;
      }
    }
  }

  // Assuming not to delete a node after the last node
  bool deleteAfter(T key) { // O(n)
    if (nodesCount < 2) {
      return false;
    } else if (nodesCount == 2) {
      if (head->val == key) {
        head->next->next = nullptr;
        delete head->next;
        head->next = head;
        --nodesCount;
        return true;
      }
      return false;
    } else {
      Node<T> *temp = head;
      while (temp->next != head) {
        if (temp->val == key) {
          Node<T> *temp2 = temp->next;
          temp->next = temp2->next;
          temp2->next = nullptr;
          delete temp2;
          --nodesCount;
          return true;
        }
        temp = temp->next;
      }
      // Since we are not going to delete a node after the last node, we don't need to process it.
      return false;
    }
  }

  // Assuming not to delete a node before the first node
  bool deleteBefore(T key) {
    if (nodesCount < 2) {
      return false;
    } else if (nodesCount == 2) {
      if (head->next->val == key) { // Deleting the first node in a list of length 2
        head = head->next;
        head->next->next = nullptr;
        delete head->next;
        head->next = head;
        --nodesCount;
        return true;
      }
      return false;
    } else {
      if (head->next->val == key) { // Deleting the first node in a list of length more than 2
        Node<T> *temp = head;
        while (temp->next != head) {
          temp = temp->next;
        }
        head = head->next;
        temp->next->next = nullptr;
        delete temp->next;
        temp->next = head;

        --nodesCount;
        return true;
      } else {
        Node<T> *temp = head;
        while (temp->next != head) {
          if (temp->next->next->val == key && temp->next->next != head) {
            Node<T> *temp2 = temp->next;
            temp->next = temp2->next;
            temp2->next = nullptr;
            delete temp2;

            --nodesCount;
            return true;
          }
          temp = temp->next;
        }
        return false;
      }
    }
  }

  int getLength() { // O(1)
    return nodesCount;
  }

  Node<T> *search(T val) { // O(n)
    if (nodesCount == 0) {
      throw runtime_error("Exception! List is empty!");
    }
    Node<T> *temp = head;
    while (temp->next != head) {
      if (temp->val == val) {
        return temp;
      }
      temp = temp->next;
    }
    if (temp->val == val) { // Processing the last node
      return temp;
    }
    throw runtime_error("Exception! Node not found!");
  }
};

int main() {
  SinglyCircularLinkedList<int> myList;
  cout << "\n>---------------<\n";
  cout << "1- Insert at head" << endl;
  cout << "2- Insert at tail" << endl;
  cout << "3- Delete at head" << endl;
  cout << "4- Delete at tail" << endl;
  cout << "5- Print the list" << endl;
  cout << "6- Get node" << endl;
  cout << "7- Test copy constructor" << endl;
  cout << "8- Insert after" << endl;
  cout << "9- Insert before" << endl;
  cout << "10- Delete after" << endl;
  cout << "11- Delete before" << endl;
  cout << "12- Search using value" << endl;
  cout << "13- Exit\n\n";
  cout << "Your choice: ";
  int choice;
  cin >> choice;
  cout << "-----\n";
  while (choice != 13) {
    if (choice == 1) {
      int element;
      cout << "Enter a element to insert at head: ";
      cin >> element;
      myList.insertAtHead(element);
      cout << "Element inserted at head successfully!";
    } else if (choice == 2) {
      int element;
      cout << "Enter a element to insert at tail: ";
      cin >> element;
      myList.insertAtTail(element);
      cout << "Element inserted at tail successfully!";
    } else if (choice == 3) {
      if (myList.deleteAtHead()) {
        cout << "Element deleted at head successfully!";
      } else {
        cout << "Could not delete an element from an empty list!";
      }
    } else if (choice == 4) {
      if (myList.deleteAtTail()) {
        cout << "Element deleted at tail successfully!";
      } else {
        cout << "Could not delete an element from an empty list!";
      }
    } else if (choice == 5) {
      cout << "List: ";
      myList.print();
    } else if (choice == 6) {
      int index;
      cout << "Enter index of the node: ";
      cin >> index;
      try {
        Node<int> *node = myList.getNode(index);
        cout << "The Node is: " << node;
      } catch (exception &e) {
        cout << e.what();
      }
    } else if (choice == 7) {
      SinglyCircularLinkedList<int> myList2(myList);
      cout << "The new list: ";
      myList2.print();
    } else if (choice == 8) {
      int key, value;
      cout << "Enter the key: ";
      cin >> key;
      cout << "Enter the value to be inserted: ";
      cin >> value;
      if (myList.insertAfter(key, value)) {
        cout << "Value inserted successfully!";
      } else {
        cout << "Insertion failed! Empty list or key not found!";
      }
    } else if (choice == 9) {
      int key, value;
      cout << "Enter the key: ";
      cin >> key;
      cout << "Enter the value to be inserted: ";
      cin >> value;
      if (myList.insertBefore(key, value)) {
        cout << "Value inserted successfully!";
      } else {
        cout << "Insertion failed! Empty list or key not found!";
      }
    } else if (choice == 10) {
      int key;
      cout << "Enter the key: ";
      cin >> key;
      if (myList.deleteAfter(key)) {
        cout << "Deleted successfully!";
      } else {
        cout << "Deletion failed! Empty list or key not found or deleting after the last node!";
      }
    } else if (choice == 11) {
      int key;
      cout << "Enter the key: ";
      cin >> key;
      if (myList.deleteBefore(key)) {
        cout << "Deleted successfully!";
      } else {
        cout << "Deletion failed! Empty list or key not found or deleting before the first node!";
      }
    } else if (choice == 12) {
      int value;
      cout << "Enter the value to search: ";
      cin >> value;
      try {
        myList.search(value);
        cout << "The value " << value << " is found!";
      } catch (exception &e) {
        cout << e.what();
      }
    } else {
      cout << "Invalid choice!";
    }

    // UNCOMMENT
    cout << "\n\nList..." << endl;
    myList.print();

    cout << "\n\n>---------------<\n";
    cout << "1- Insert at head" << endl;
    cout << "2- Insert at tail" << endl;
    cout << "3- Delete at head" << endl;
    cout << "4- Delete at tail" << endl;
    cout << "5- Print the list" << endl;
    cout << "6- Get node" << endl;
    cout << "7- Test copy constructor" << endl;
    cout << "8- Insert after" << endl;
    cout << "9- Insert before" << endl;
    cout << "10- Delete after" << endl;
    cout << "11- Delete before" << endl;
    cout << "12- Search using value" << endl;
    cout << "13- Exit\n\n";
    cout << "Your choice: ";
    cin >> choice;
    cout << "-----\n";
  }

  return 0;
}