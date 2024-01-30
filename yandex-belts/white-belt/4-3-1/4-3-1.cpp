#include <iostream>
#include <cassert>
using namespace std;

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
        return m_numerator;
    }

    int Denominator() const {
        return m_denominator;
    }

    int Sign() const {
        return m_sign;
    }

private:
    int m_numerator;
    int m_denominator;
    int m_sign;

};

bool operator==(const Rational& lhs, const Rational& rhs) {
  return ((rhs.Numerator() == lhs.Numerator()) && (rhs.Denominator() == lhs.Denominator()) && (rhs.Sign() == lhs.Sign()));
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    if (lhs.Numerator() == 0 && rhs.Denominator() == 0) {
      return {0, 1};
    }
    if (lhs.Denominator() == rhs.Denominator()) {
      return Rational{(lhs.Sign() * lhs.Numerator() + rhs.Sign() * rhs.Numerator()), lhs.Denominator()};
    }
    int lcm = getLcm(lhs.Denominator(), rhs.Denominator());
    int lhsAddMult = lcm / lhs.Denominator();
    int rhsAddMult = lcm / rhs.Denominator();
    int newDenominator = lcm;
    int newNumerator = lhs.Sign() * lhs.Numerator() * lhsAddMult + rhs.Sign() * rhs.Numerator() * rhsAddMult;
    return Rational{newNumerator, newDenominator};

}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    if (lhs.Numerator() == 0 && rhs.Numerator() == 0) {
      return {0, 1};
    }
    int lcm = getLcm(lhs.Denominator(), rhs.Denominator());
    int lhsAddMult = lcm / lhs.Denominator();
    int rhsAddMult = lcm / rhs.Denominator();
    int newDenominator = lcm;
    int newNumerator = lhs.Sign() * lhs.Numerator() * lhsAddMult - rhs.Sign() * rhs.Numerator() * rhsAddMult;
    return Rational{newNumerator, newDenominator};

}

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
