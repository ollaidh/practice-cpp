// #include <_types/_intmax_t.h>
#include <exception>
#include <iostream>
#include <cassert>
#include <ostream>
#include <sstream>
#include <set>
#include <map>
#include <stdexcept>
#include <string>

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
          throw std::invalid_argument("Invalid argument");
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
      throw std::domain_error("Division by zero");
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

class StandardFractionCalculator {
public:
  StandardFractionCalculator (Rational fractionLhs, Rational fractionRhs, std::string operation)
  : m_fractionLhs(fractionLhs)
  , m_fractionRhs(fractionRhs)
  , m_operation(operation)
  {}
  Rational calculate() {
    if (m_operation == "+") {
      return m_fractionLhs + m_fractionRhs;
    }
    if (m_operation == "-") {
      return m_fractionLhs - m_fractionRhs;
    }
    if (m_operation == "*") {
      return m_fractionLhs * m_fractionRhs;
    }
    try {
      return m_fractionLhs / m_fractionRhs;
    } catch (std::invalid_argument& ex) {
      throw std::invalid_argument(ex.what());
    }
  }
private:
  Rational m_fractionRhs;
  Rational m_fractionLhs;
  std::string m_operation;

};

StandardFractionCalculator parseCalculatorParameters(stringstream& ss) {
  int numerator1;
  int numerator2;
  int denominator1;
  int denominator2;
  std::string sign;
  ss >> numerator1;
  ss.ignore(1);
  ss >> denominator1;
  ss.ignore(1);
  ss >> sign;
  ss >> numerator2;
  ss.ignore(1);
  ss >> denominator2;
  if (denominator1 == 0 || denominator2 == 0) {
    throw std::invalid_argument("Invalid argument");
  }
  return StandardFractionCalculator{Rational{numerator1, denominator1},
          Rational{numerator2, denominator2},
            sign};

};

int main() {
  int numerator1;
  int numerator2;
  int denominator1;
  int denominator2;
  std::string sign;
  std::cin >> numerator1;
  std::cin.ignore(1);
  std::cin >> denominator1;
  std::cin >> sign;
  std::cin >> numerator2;
  std::cin.ignore(1);
  std::cin >> denominator2;

  // std::cout << numerator1 << " ";
  // std::cout << denominator1 << " ";
  // std::cout << sign << " ";
  // std::cout << numerator2 << " ";
  // std::cout << denominator2 << " ";


  try {
        StandardFractionCalculator calc{Rational{numerator1, denominator1},
                                        Rational{numerator2, denominator2},
                                        sign};
        std::cout << calc.calculate();

  } catch (exception& ex) {
    std::cout << ex.what() << std::endl;
  }
  return 0;
}
