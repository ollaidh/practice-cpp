#include <iostream>
#include <cassert>
#include <ostream>
#include <sstream>
#include <set>
#include <map>
#include <stdexcept>

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
        return m_numerator;
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
    if (rhs.Numerator() == 0) {
      throw std::domain_error("Divizion by zero!");
    }
    Rational newRhs(rhs.Sign() * rhs.Denominator(), rhs.Numerator());
    return lhs * newRhs;
}

ostream& operator<<(ostream& stream, const Rational& rational) {
  std::string sign = "";
  if (rational.Sign() < 0) {
    sign = "-";
  }
  stream << sign << rational.Numerator() << "/" << rational.Denominator();
  return stream;
}

istream& operator>>(istream& stream, Rational& rational) {
    int numerator;
    int denominator;
    if (stream >> numerator) {
      stream.ignore(1);
      if (stream >> denominator) {
        rational = {numerator, denominator};
      }
    }
  return stream;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
  if (lhs.Sign() < rhs.Sign()) {
    return true;
  } else if (lhs.Sign() < rhs.Sign()) {
    return false;
  }
  return lhs.Sign() * lhs.Numerator() * rhs.Denominator() < rhs.Sign() * rhs.Numerator() * lhs.Denominator();

}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
