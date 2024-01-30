#include <iostream>
#include <cassert>
#include <ostream>
#include <sstream>

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

int main() {
    {
        ostringstream output;
        Rational aaa = Rational(-6, 8);
        output << aaa;
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}