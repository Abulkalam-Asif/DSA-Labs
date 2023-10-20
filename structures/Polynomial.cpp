#include <cmath>
#include <exception>
#include <iostream>
using namespace std;

class Polynomial {
private:
  int *poly;
  int degree;     // current degree of the polynomial
  int max_degree; // maximum degree of the polynomial allowed (size of the array)

public:
  Polynomial(int max_deg) {
    degree = 0;
    max_degree = max_deg;
    poly = new int[max_deg + 1]{0}; // if max_degree is 2, the array will be of size 3 with x^2, x and constant
  }
  Polynomial(const Polynomial &obj) {
    degree = obj.degree;
    max_degree = obj.max_degree;
    poly = new int[max_degree + 1];
    for (size_t i = 0; i <= max_degree; i++) {
      poly[i] = obj.poly[i];
    }
  }
  int get_degree() const {
    return degree;
  }
  Polynomial &operator=(const Polynomial &obj) {
    // Clearing the caller polynomial if it already has values in it
    if (this->degree != 0 || this->max_degree != 0) {
      delete[] this->poly;
    }
    this->degree = obj.degree;
    this->max_degree = obj.max_degree;
    this->poly = new int[this->max_degree + 1];
    for (size_t i = 0; i <= this->max_degree; i++) {
      this->poly[i] = obj.poly[i];
    }
    return *this;
  }
  void add_term(int coefficient, int deg) {
    if (deg > max_degree) {
      throw std::runtime_error("Exception: Degree must be less than max degree!");
    } else {
      poly[deg] = coefficient;
      // Increasing degree if a higher degree term is added
      if (deg > degree) {
        degree = deg;
      }
    }
  }
  void remove_term(int deg) {
    if (deg > degree) {
      throw std::runtime_error("Exception: Term does not exist!");
    } else {
      poly[deg] = 0;
      // Decreasing the degree if the term with highest degree is removed
      if (deg == degree) {
        if (deg == 0) {
          degree = deg;
          return;
        }
        for (size_t i = deg - 1; i >= 0; i--) {
          if (poly[i] != 0) {
            degree = i;
            return;
          }
        }
      }
    }
  }
  void set_coeffecient(int coefficient, int deg) {
    if (deg > max_degree) {
      throw std::runtime_error("Exception: Degree must be less than max degree!");
    } else {
      poly[deg] = coefficient;
      // Increasing degree if a higher degree term is added
      if (deg > degree) {
        degree = deg;
      }
    }
  }
  friend ostream &operator<<(ostream &os, const Polynomial &poly) {
    int lowest = 0;
    for (size_t i = 0; i <= poly.degree; i++) {
      if (poly.poly[i] != 0) {
        lowest = i;
        break;
      }
    }
    for (int i = poly.degree; i >= 0; i--) {
      if (poly.poly[i] != 0) {
        if (poly.poly[i] > 1) {
          os << poly.poly[i];
        } else if (poly.poly[i] > 0 && i == 0) {
          os << poly.poly[i];
        }
        os << (i > 0 ? "x" : "");
        if (i > 1) {
          os << "^" << i;
        }
        if (i > lowest) {
          os << " + ";
        }
      }
    }
    return os;
  }
  double operator()(double x) const {
    double result = 0;
    for (size_t i = 0; i <= this->degree; i++) {
      if (this->poly[i] != 0) {
        result += this->poly[i] * pow(x, i);
      }
    }
    return result;
  }
  Polynomial operator+(const Polynomial &other) {
    Polynomial result = (this->max_degree > other.max_degree) ? *this : other;
    Polynomial lower = (this->max_degree > other.max_degree) ? other : *this;

    for (size_t i = 0; i <= lower.max_degree; i++) {
      result.poly[i] += lower.poly[i];
    }
    return result;
  }
  Polynomial operator*(const Polynomial &other) {
    Polynomial result(this->max_degree + other.max_degree);
    for (size_t i = 0; i <= this->max_degree; i++) {
      for (size_t j = 0; j <= other.max_degree; j++) {
        result.poly[i + j] += this->poly[i] * other.poly[j];
      }
    }
    // setting the degree of the result
    for (size_t i = result.max_degree; i >= 0; i--) {
      if (poly[i] != 0) {
        result.degree = i;
        break;
      }
    }
    return result;
  }
  ~Polynomial() {
    delete[] poly;
  }
};

int main() {
  Polynomial p1(3);
  try {
    p1.add_term(2, 2);
    p1.add_term(2, 1);
    p1.add_term(2, 0);
    cout << "P1 after adding terms:\t\t(" << p1 << ")" << endl;
    cout << "Degree of P1:\t\t\t" << p1.get_degree() << endl;
    Polynomial p2(p1);
    cout << "P2 using copy constructor:\t(" << p2 << ")" << endl;
    p2 = p1;
    cout << "P2 using assignment operator:\t(" << p2 << ")" << endl;
    cout << "P2 with x = 2:\t\t\t" << p2(2) << endl;
    p1.remove_term(2);
    p1.remove_term(1);
    p1.remove_term(0);
    cout << "P1 after removing terms:\t(" << p1 << ")" << endl;
    cout << "Degree of P1:\t\t\t" << p1.get_degree() << endl;

    Polynomial p3(2), p4(3);
    p3.add_term(1, 0);
    p3.add_term(1, 1);
    p3.add_term(1, 2);
    p4.add_term(1, 0);
    p4.add_term(1, 1);
    p4.add_term(1, 2);
    p4.add_term(1, 3);
    cout << "\nAddition:\n(" << p3 << ")  +  (" << p4 << ")  =  " << p3 + p4 << endl;
    cout << "\nMultiplication:\n(" << p3 << ")  +  (" << p4 << ")  =  " << p3 * p4 << endl;

  } catch (exception &e) {
    cout << e.what() << endl;
  }

  return 0;
}