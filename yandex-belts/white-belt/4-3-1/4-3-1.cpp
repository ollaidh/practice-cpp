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
    int lcm = getLcm(lhs.Denominator(), rhs.Denominator());
    int lhsAddMult = lcm / lhs.Denominator();
    int rhsAddMult = lcm / rhs.Denominator();
    int newDenominator = lcm;
    int newNumerator = lhs.Sign() * lhs.Numerator() * lhsAddMult + rhs.Sign() * rhs.Numerator() * rhsAddMult;
    return Rational{newNumerator, newDenominator};

}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational newRhs{rhs.Numerator() * rhs.Sign() * (-1), rhs.Denominator()};
    return lhs + newRhs;

}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.Sign() * rhs.Sign() * lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());

}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational newRhs(rhs.Sign() * rhs.Denominator(), rhs.Numerator());
    return lhs * newRhs;
}

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}