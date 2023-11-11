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
  // For the sake of printing a node
  friend ostream &operator<<(ostream &o, const Node<T> *obj) {
    o << obj->data;
    return o;
  }
};

template <typename T>
class DoublyLinearLinkedList {
private:
  Node<T> *head;
  Node<T> *tail;
  int nodesCount;

public:
  DoublyLinearLinkedList() : nodesCount(0), head(nullptr), tail(nullptr) {}

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

  Node<T> *getNode(int n) { // O(n) | Max iterations(n/2)

    if (head) { // If head is not null
      Node<T> *temp = nullptr;
      if (n <= nodesCount / 2) { // If node is in the first half of the list
        temp = head;
        while (temp->next) {
          // Decrementing the n. When it reaches 0, we have reached the desired node.
          if (n == 0) {
            return temp;
          }
          --n;
          temp = temp->next;
        }
      } else {
        temp = tail;
        n = nodesCount - 1 - n; // Indexing from the end

        if (n < 0) { // Returning tail if index is greater than nodesCount
          return temp;
        } else {
          while (temp->prev) {
            if (n == 0) {
              return temp;
            }
            --n;
            temp = temp->prev;
          }
        }
      }
      return temp;
    } else {
      throw runtime_error("Exception! List is empty!");
    }
  }

  bool insertAfter(T key, T value) { // O(n)
    if (head) {
      Node<T> *temp = head;
      while (temp) {
        if (temp->data == key) {
          Node<T> *temp2 = nullptr;
          if (temp->next != nullptr) { // If not on tail
            temp2 = temp->next;
          }
          // Connecting the new node with the previous node
          temp->next = new Node<T>(value);
          temp->next->prev = temp;
          if (temp == tail) {
            // Moving the tail to new node if it is inserted in the end
            tail = temp->next;
          }
          if (temp2) {
            // Connecting the new node with the next node if not on tail
            temp->next->next = temp2;
            temp2->prev = temp->next;
          }
          ++nodesCount;
          return true;
        }
        temp = temp->next;
      }
      return false;
    } else {
      throw runtime_error("Exception! List is empty!");
    }
  }

  bool insertBefore(T key, T value) { // O(n)
    if (head) {
      Node<T> *temp = head;
      while (temp) {
        if (temp->data == key) {
          Node<T> *temp2 = nullptr;
          if (temp->prev != nullptr) { // If not on head
            temp2 = temp->prev;
          }
          // Connecting the new node with the next node
          temp->prev = new Node<T>(value);
          temp->prev->next = temp;
          if (temp == head) {
            // Moving the head to new node if it is inserted in the start
            head = temp->prev;
          }
          if (temp2) {
            // Connecting the new node with the previouts node if not on head
            temp->prev->prev = temp2;
            temp2->next = temp->prev;
          }
          ++nodesCount;
          return true;
        }
        temp = temp->next;
      }
      return false;
    } else {
      throw runtime_error("Exception! List is empty!");
    }
  }

  bool deleteAfter(T key) { // O(n)
    if (nodesCount < 2) {
      // If the list is empty or there is only 1 node
      return false;
    } else {
      Node<T> *temp = head;
      while (temp->next->next) { // looping till the 2nd last node
        if (temp->data == key) {
          Node<T> *temp2 = temp->next->next;
          // The prev and next pointers of the node to be deleted are made nullified
          temp->next->prev = nullptr;
          temp->next->next = nullptr;
          // Creating connection with the next node
          temp2->prev = temp;
          // deleting the target node.
          delete temp->next;
          // Completing the connection with the previous node
          temp->next = temp2;

          --nodesCount;
          return true;
        }
        temp = temp->next;
      }
      if (temp->data == key) { // If we have to delete the last node
        temp->next->prev = nullptr;
        delete temp->next;
        temp->next = nullptr;
        tail = temp;

        --nodesCount;
        return true;
      } else {
        return false;
      }
    }
  }

  bool deleteBefore(T key) { // O(n)
    if (nodesCount < 2 || head->data == key) {
      // If the list is empty or there is only 1 node or the key is on the head node
      return false;
    } else {
      Node<T> *temp = head->next; // Starting from the 2nd node
      if (temp->data == key) {    // If deleting the node on the head
        temp->prev->next = nullptr;
        delete temp->prev;
        temp->prev = nullptr;
        head = temp;
        --nodesCount;
        return true;
      } else {
        while (temp) {
          if (temp->data == key) {
            Node<T> *temp2 = temp->prev->prev;
            // The prev and next pointers of the node to be deleted are made nullified
            temp->prev->prev = nullptr;
            temp->prev->next = nullptr;
            // Creating connection with the previous node
            temp2->next = temp;
            // deleting the target node.
            delete temp->prev;
            // Completing the connection with the previous node
            temp->prev = temp2;

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

  Node<T> *search(T x) { // O(n)
    if (head) {
      Node<T> *temp = head;
      if (nodesCount == 1 && head->data != x) {
        throw runtime_error("No node found with the given value!");
      } else {
        while (temp) {
          if (temp->data == x) {
            return temp;
          }
          temp = temp->next;
        }
        throw runtime_error("No node found with the given value!");
      }
    } else {
      throw runtime_error("Exception! List is empty!");
    }
  }

  void sort() { // O(n^3)
    if (nodesCount == 0) {
      throw runtime_error("Exception! List is empty!");
    } else if (nodesCount > 1) {
      Node<T> *target = nullptr;
      int i = 0;
      while (target != tail) {
        target = getNode(i);
        Node<T> *temp = target;
        Node<T> *currSmallest = temp;
        while (temp) { // Finding the smallest element
          if (temp->data < currSmallest->data) {
            currSmallest = temp;
          }
          temp = temp->next;
        }
        if (currSmallest != target) { // If the smallest is not already at its destination
          // Removing
          if (tail == currSmallest) { // When removing from the tail
            currSmallest->prev->next = nullptr;
            tail = currSmallest->prev;
          } else { // When removing from the middle
            currSmallest->next->prev = currSmallest->prev;
            currSmallest->prev->next = currSmallest->next;
          }
          // Bringing
          if (target == head) { // When bringing at the head
            currSmallest->next = head;
            currSmallest->prev = nullptr;
            head->prev = currSmallest;
            head = currSmallest;
          } else { // When bringing at any target position
            Node<T> *prevSmallest = target->prev;
            currSmallest->next = prevSmallest->next;
            prevSmallest->next->prev = currSmallest;
            prevSmallest->next = currSmallest;
            currSmallest->prev = prevSmallest;
          }
        }
        ++i;
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
  cout << "7- Get a node" << endl;
  cout << "8- Insert after" << endl;
  cout << "9- Insert before" << endl;
  cout << "10- Delete after" << endl;
  cout << "11- Delete before" << endl;
  cout << "12- Get length" << endl;
  cout << "13- Search" << endl;
  cout << "14- Sort" << endl;
  cout << "15- Exit" << endl;
  cout << "\nYour choice: ";
  int choice;
  cin >> choice;
  cout << "-----\n";
  while (choice != 15) {
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
    } else if (choice == 7) {
      int index;
      do {
        cout << "Enter the index of node >= 0: ";
        cin >> index;
      } while (index < 0);

      try {
        cout << "The node at index " << index << " is " << myList.getNode(index);
      } catch (exception &e) {
        cout << e.what();
      }
    } else if (choice == 8) {
      int key, value;
      cout << "Enter the key: ";
      cin >> key;
      cout << "Enter the value to be inserted: ";
      cin >> value;
      try {
        if (myList.insertAfter(key, value)) {
          cout << "Value inserted successfully!";
        } else {
          cout << "Insertion failed!";
        }
      } catch (exception &e) {
        cout << e.what();
      }
    } else if (choice == 9) {
      int key, value;
      cout << "Enter the key: ";
      cin >> key;
      cout << "Enter the value to be inserted: ";
      cin >> value;
      try {
        if (myList.insertBefore(key, value)) {
          cout << "Value inserted successfully!";
        } else {
          cout << "Insertion failed!";
        }
      } catch (exception &e) {
        cout << e.what();
      }
    } else if (choice == 10) {
      int key;
      cout << "Enter the key: ";
      cin >> key;
      if (myList.deleteAfter(key)) {
        cout << "Deleted successfully!";
      } else {
        cout << "Deletion failed!";
      }
    } else if (choice == 11) {
      int key;
      cout << "Enter the key: ";
      cin >> key;
      if (myList.deleteBefore(key)) {
        cout << "Deleted successfully!";
      } else {
        cout << "Deletion failed!";
      }
    } else if (choice == 12) {
      cout << "The length of the list is: " << myList.getLength();
    } else if (choice == 13) {
      int value;
      cout << "Enter the value to search: ";
      cin >> value;
      try {
        cout << "The value " << myList.search(value) << " is found!";
      } catch (exception &e) {
        cout << e.what();
      }
    } else if (choice == 14) {
      try {
        myList.sort();
        cout << "List sorted successfully!";
      } catch (exception &e) {
        cout << e.what();
      }
    } else {
      cout << "Invalid choice! Try again.";
    }

    // UNDO
    cout << "\nList: ";
    myList.printList();

    cout << "\n\n>---------------<\n";
    cout << "1- Insert at head" << endl;
    cout << "2- Insert at tail" << endl;
    cout << "3- Delete at head" << endl;
    cout << "4- Delete at tail" << endl;
    cout << "5- Test copy constructor" << endl;
    cout << "6- Print" << endl;
    cout << "7- Get a node" << endl;
    cout << "8- Insert after" << endl;
    cout << "9- Insert before" << endl;
    cout << "10- Delete after" << endl;
    cout << "11- Delete before" << endl;
    cout << "12- Get length" << endl;
    cout << "13- Search" << endl;
    cout << "14- Sort" << endl;
    cout << "15- Exit" << endl;
    cout << "\nYour choice: ";
    cin >> choice;
    cout << "-----\n";
  }

  return 0;
}

// 2 5 2 2 2 8 2 2 2 5 2 1
// 2 7 2 4 2 3 2 4 2 7 2 2
// 2 1 2 3 2 6 2 3 2 1 2 4
// 2 9 2 2 2 9 2 6 2 2 2 7
// 2 4 2 8 2 4 2 1 2 8 2 3