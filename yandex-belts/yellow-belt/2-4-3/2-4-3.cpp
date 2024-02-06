#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};


#ifdef LOCAL_RUN

int getSign(int a, int b) {
  if ((a < 0 && b > 0) || (a > 0 && b < 0)) {
    return -1;
  }
  return 1;
}

int getGcd(int a, int b) {
  while (a != 0 and b != 0) {
    if (a > b) {
        a = a % b;
    }
    else {
        b = b % a;
    }
  }
  return (a + b);
}

int getLcm(int a, int b) {
  int gcd = getGcd(a, b);
  return a * b / gcd;
}

class Rational {
public:
    Rational()
    : m_numerator(0)
    , m_denominator(1)
    , m_sign(1)
    {}

    Rational(int numerator, int denominator) {
        if (denominator == 0) {
          throw std::invalid_argument("Zero denominator!");
        }
        if (numerator == 0) {
          m_numerator = 0;
          m_denominator = 1;
          m_sign = 1;
        } else {
          m_sign = getSign(numerator, denominator);
          numerator = abs(numerator);
          denominator = abs(denominator);
          int gcd = getGcd(numerator, denominator);
          m_numerator = numerator / gcd;
          m_denominator = denominator / gcd;
        }

    }

    int Numerator() const {
        return m_numerator * m_sign;
    }

    int Denominator() const {
        return m_denominator;
    }

    int Sign() const {
      return m_sign;
    }

    void setSign(int sign) {
      m_sign = sign;
    }

    void setNumerator(int numerator) {
      m_numerator = numerator;
    }

    void setDenominator(int denominator) {
      m_denominator = denominator;
    }

private:
    int m_numerator;
    int m_denominator;
    int m_sign;

};

#endif

void TestPredefined() {
  AssertEqual(Rational().Numerator(), 0);
  AssertEqual(Rational().Denominator(), 1);
  AssertEqual(Rational(1, 1).Numerator(), 1);
  AssertEqual(Rational(1, 1).Denominator(), 1);
  AssertEqual(Rational(3, 5).Numerator(), 3);
  AssertEqual(Rational(3, 5).Denominator(), 5);
  AssertEqual(Rational(-5, 4).Numerator(), -5);
  AssertEqual(Rational(-5, 4).Denominator(), 4);
  AssertEqual(Rational(5, -4).Numerator(), -5);
  AssertEqual(Rational(5, -4).Denominator(), 4);
  AssertEqual(Rational(0, 100).Numerator(), 0);
  AssertEqual(Rational(0, 100).Denominator(), 1);

}

int main() {
  TestRunner runner;
  runner.RunTest(TestPredefined, "TestPredefined");
  return 0;
}
