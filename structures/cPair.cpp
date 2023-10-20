#include <iostream>
using namespace std;

template <class T1, class T2>
class cPair {
private:
  T1 key;
  T2 value;

public:
  cPair() {
    key = T1(0);
    value = T2(0);
  }
  cPair(int key, int value) {
    this->key = key;
    this->value = value;
  }
  cPair(const cPair &obj) : key(obj.key), value(obj.value) {}

  // can be called without the object, just with scope resolution operator
  static cPair makePair(T1 key, T2 value) {
    return cPair(key, value);
  }

  cPair &operator=(const cPair &obj) {
    if (this != &obj) {
      key = obj.key;
      value = obj.value;
    }
    return *this;
  }
  bool operator>=(const cPair &obj) {
    if (this->key >= obj.key) {
      return true;
    } else if (this->value >= obj.value) {
      return true;
    }
    return false;
  }
  friend ostream &operator<<(ostream &out, const cPair &obj) {
    out << obj.key << ", " << obj.value;
    return out;
  }
  friend istream &operator>>(istream &in, cPair &obj) {
    in >> obj.key;
    in >> obj.value;
    return in;
  }
};

int main() {
  cPair<int, int> simplePair;
  cPair<int, int> parameterizedPair(99, 100);
  cPair<int, int> copyPair(parameterizedPair);
  cPair<int, int> assignmentPair = parameterizedPair;
  cout << "Enter values: ";
  cin >> parameterizedPair;
  cPair<int, int>
      makePairPair = cPair<int, int>::makePair(32, 74);
  cout << "simple pair: " << simplePair << endl;
  cout << "parameterized pair: " << parameterizedPair << endl;
  cout << "copy pair: " << copyPair << endl;
  cout << "assignment pair: " << assignmentPair << endl;
  cout << "makePair pair: " << makePairPair << endl;

  return 0;
}