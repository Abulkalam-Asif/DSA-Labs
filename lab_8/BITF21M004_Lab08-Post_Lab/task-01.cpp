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

  void combine(DoublyCircularLinkedList &list1, DoublyCircularLinkedList &list2) { // O(1)
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

  // We can assume that both lists (which are being merged)contain the same number of elements / nodes
  void shuffleMerge(DoublyCircularLinkedList &list1, DoublyCircularLinkedList &list2) { // O(n)
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
      Node<T> *temp = this->head;
      Node<T> *temp2 = list2.head;
      Node<T> *temp2Next = temp2->next;
      while (temp->next != this->head || temp2Next != list2.head) {
        temp2->next = temp->next;
        temp2->next->prev = temp2;
        temp2->prev = temp;
        temp->next = temp2;

        temp2 = temp2Next;
        temp2Next = temp2Next->next;
        temp = temp->next->next;
      }
      // For tail node
      temp2->next = temp->next;
      temp2->next->prev = temp2;
      temp2->prev = temp;
      temp->next = temp2;

      this->nodesCount = list1.nodesCount + list2.nodesCount;
      list1.head = nullptr;
      list2.head = nullptr;
    }
  }

  void splitList(DoublyCircularLinkedList &list1, DoublyCircularLinkedList &list2) { // O(n)
    if (this->nodesCount == 0) {
      return;
    } else if (this->nodesCount == 1) {
      list1.head = this->head;
      this->head = nullptr;
      list1.nodesCount = this->nodesCount;
    } else {
      list1.head = this->head;
      Node<T> *temp = this->head;
      int mid = this->nodesCount / 2;
      if (this->nodesCount % 2 != 0) {
        ++mid;
      }
      int currentNode = 1;
      while (currentNode < mid) {
        temp = temp->next;
        ++currentNode;
      }
      list2.head = temp->next;
      list2.head->prev = list1.head->prev;
      list2.head->prev->next = list2.head;
      list1.head->prev = temp;
      temp->next = list1.head;
      list1.nodesCount = mid;
      list2.nodesCount = this->nodesCount - mid;
      this->head = nullptr;
    }
  }

  bool isSorted() const { // O(n)
    if (nodesCount == 0) {
      throw runtime_error("Exception! List is empty.");
    } else {
      if (nodesCount == 1) {
        return true;
      } else {
        Node<T> *temp = head->next;
        while (temp != head) {
          if (temp->data < temp->prev->data) {
            return false;
          }
          temp = temp->next;
        }
        return true;
      }
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
  cout << "5- Shuffle merge" << endl;
  cout << "6- Split the list" << endl;
  cout << "7- Is sorted?" << endl;
  cout << "8- Exit" << endl;
  cout << "\nYour choice: ";
  int choice;
  cin >> choice;
  cout << "-----\n";
  while (choice != 8) {
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
    } else if (choice == 5) {
      DoublyCircularLinkedList<int> list1, list2, list3;
      int element = 0;
      cout << "Note: Both lists should have the same number of elements!" << endl;
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
      if (list1.countNodes() == list2.countNodes()) {
        list3.shuffleMerge(list1, list2);
        cout << "The shuffle merged list is: ";
        list3.display();
      } else {
        cout << "The two lists have different number of elements";
      }
    } else if (choice == 6) {
      DoublyCircularLinkedList<int> list1, list2, list3;
      int element = 0;
      cout << "Enter elements of list (-1 to exit): ";
      cin >> element;
      while (element != -1) {
        list1.insertAtTail(element);
        cin >> element;
      }
      list1.splitList(list2, list3);
      cout << "The two lists are:\nList 1: ";
      list2.display();
      cout << "\nList 2: ";
      list3.display();
    } else if (choice == 7) {
      try {
        if (myList.isSorted()) {
          cout << "The list is sorted";
        } else {
          cout << "The list is NOT sorted";
        }
      } catch (exception &e) {
        cout << e.what();
      }
    } else {
      cout << "Invalid choice! Try again.";
    }

    cout << "\n\n>---------------<\n";
    cout << "1- Insert at head" << endl;
    cout << "2- Insert at tail" << endl;
    cout << "3- Display the list" << endl;
    cout << "4- Combine lists" << endl;
    cout << "5- Shuffle merge" << endl;
    cout << "6- Split the list" << endl;
    cout << "7- Is sorted?" << endl;
    cout << "8- Exit" << endl;
    cout << "\nYour choice: ";
    cin >> choice;
    cout << "-----\n";
  }

  return 0;
}