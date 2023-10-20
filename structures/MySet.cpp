#include <iostream>
using namespace std;

template <typename T>
class MySet {
private:
  T* set;
  int size;

public:
  MySet() {
    size = 0;
    set = new T[size];
  }
  MySet(const MySet<T>& obj) {
    set = new T[obj.size];
    size = obj.size;
    for (int i = 0; i < size; i++) {
      set[i] = obj.set[i];
    }
  }
  bool insert(const T& val) {
    for (int i = 0; i < size; i++) {
      if (val == set[i]) {
        return false;
      }
    }
    T* tempSet = new T[size];
    for (size_t i = 0; i < size; i++) {
      tempSet[i] = set[i];
    }
    delete[] set;
    ++size;
    set = new T[size];
    for (size_t i = 0; i < size - 1; i++) {
      set[i] = tempSet[i];
    }
    set[size - 1] = val;
    delete[] tempSet;
    return true;
  }
  void erase(const T val) {
    bool found = false;
    for (size_t i = 0; i < size; ++i) {
      if (val == set[i]) {
        found = true;
        break;
      }
    }
    if (found) {
      T* tempSet = new T[size];
      for (size_t i = 0; i < size; i++) {
        tempSet[i] = set[i];
      }
      delete[] set;
      --size;
      set = new T[size];
      for (size_t i = 0, j = 0; i < size; i++, j++) {
        if (tempSet[j] == val) {
          ++j;
        }
        set[i] = tempSet[j];
      }
      delete[] tempSet;
    }
  }
  void clear() {
    delete[] set;
    size = 0;
    set = new T[size];
  }
  int get_size() const {
    return size;
  }
  bool contains(const T val) const {
    for (size_t i = 0; i < size; ++i) {
      if (set[i] == val) {
        return true;
      }
    }
    return false;
  }
  bool is_empty() {
    if (size == 0) {
      return true;
    }
    return false;
  }
  MySet<T> union_of_sets(const MySet<T>& other) {
    MySet<T> returnSet(*this);
    for (size_t i = 0; i < other.get_size(); i++) {
      returnSet.insert(other.set[i]);
    }
    return returnSet;
  }
  MySet<T>& operator=(const MySet<T>& other) {
    // Clearing the caller set if it already has values in it
    if (size != 0) {
      delete[] set;
    }
    size = other.size;
    set = new T[size];
    for (int i = 0; i < size; i++) {
      set[i] = other.set[i];
    }
    return *this;
  }
  friend ostream& operator<<(ostream& out, MySet<T>& obj) {
    for (size_t i = 0; i < obj.size; i++) {
      out << obj.set[i];
      if (i != obj.size - 1) {
        cout << ", ";
      }
    }
    return out;
  }
  ~MySet() {
    delete[] set;
  }
};

int main() {
  cout << "Integer set:\n---------------\n\n";
  MySet<int> set1;
  set1.insert(3);
  set1.insert(1);
  set1.insert(2);
  set1.insert(3);
  set1.insert(2);
  cout << "Set 1 Before erasing 3:\t\t\t(" << set1 << ")" << endl;
  set1.erase(3);
  cout << "Set 1 After erasing 3:\t\t\t(" << set1 << ")" << endl;
  MySet<int> set2(set1);
  cout << "Set 2 using copy constructor:\t\t(" << set2 << ")" << endl;
  set2 = set1;
  cout << "Set 2 after assignment from Set 1:\t(" << set2 << ")" << endl;
  cout << "Does Set 2 contain 2?\t\t\t" << set2.contains(2) << endl;
  cout << "Does Set 2 contain 3?\t\t\t" << set2.contains(3) << endl;
  cout << "Set 1 before clearing:\t\t\t(" << set1 << ")" << endl;
  cout << "Is Set 1 empty:\t\t\t\t" << set1.is_empty() << endl;
  set1.clear();
  cout << "Set 1 after clearing:\t\t\t(" << set1 << ")" << endl;
  cout << "Is Set 1 empty:\t\t\t\t" << set1.is_empty() << endl;

  MySet<int> setU1, setU2, intUnionSet;
  setU1.insert(1);
  setU1.insert(2);
  setU1.insert(3);
  setU1.insert(4);
  setU2.insert(2);
  setU2.insert(3);
  setU2.insert(8);
  setU2.insert(9);
  intUnionSet = setU1.union_of_sets(setU2);
  cout << "Union:\n\t(" << setU1 << ")  U  (" << setU2 << ")  =  (" << intUnionSet << ")" << endl;


  cout << "\n\n\nString set:\n---------------\n\n";
  MySet<string> strSet1;
  strSet1.insert("apple");
  strSet1.insert("banana");
  strSet1.insert("orange");
  strSet1.insert("banana");
  strSet1.insert("apple");
  cout << "Set 1 Before erasing apple:\t\t(" << strSet1 << ")" << endl;
  strSet1.erase("apple");
  cout << "Set 1 After erasing apple:\t\t(" << strSet1 << ")" << endl;
  MySet<string> strSet2(strSet1);
  cout << "Set 2 using copy constructor:\t\t(" << strSet2 << ")" << endl;
  strSet2 = strSet1;
  cout << "Set 2 after assignment from Set 1:\t(" << strSet2 << ")" << endl;
  cout << "Does Set 2 contain orange?\t\t" << strSet2.contains("orange") << endl;
  cout << "Does Set 2 contain apple?\t\t" << strSet2.contains("apple") << endl;
  cout << "Set 1 before clearing:\t\t\t(" << strSet1 << ")" << endl;
  cout << "Is Set 1 empty:\t\t\t\t" << strSet1.is_empty() << endl;
  strSet1.clear();
  cout << "Set 1 after clearing:\t\t\t(" << strSet1 << ")" << endl;
  cout << "Is Set 1 empty:\t\t\t\t" << strSet1.is_empty() << endl;

  MySet<string> strSetU1, strSetU2, strUnionSet;
  strSetU1.insert("Suzuki");
  strSetU1.insert("Toyota");
  strSetU2.insert("Toyota");
  strSetU2.insert("Bugatti");
  strSetU2.insert("Fiat");
  strUnionSet = strSetU1.union_of_sets(strSetU2);
  cout << "Union:\n\t(" << strSetU1 << ")  U  (" << strSetU2 << ")  =  (" << strUnionSet << ")" << endl;

  return 0;
}