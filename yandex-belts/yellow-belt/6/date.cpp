#include "date.h"

#include <iostream>
#include <sstream>
#include <iomanip>

Date::Date()
{
    m_year = 0;
    m_month = 0;
    m_day = 0;
}

Date::Date(int year, int month, int day)
{
    m_year = year;
    m_month = month;
    m_day = day;
}

int Date::GetYear() const {
return m_year;
}

int Date::GetMonth() const {
return m_month;
}

int Date::GetDay() const {
return m_day;
}

bool operator<(const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() != rhs.GetYear()) {
    return lhs.GetYear() < rhs.GetYear();
  }
  if (lhs.GetMonth() != rhs.GetMonth()) {
    return lhs.GetMonth() < rhs.GetMonth();
  }
  return lhs.GetDay() < rhs.GetDay();
}

std::ostream& operator<<(std::ostream& stream, const Date& date) {
  stream << std::setw(4);
  stream << std::setfill('0');
  stream << date.GetYear() << "-";
  stream << std::setw(2);
  stream << std::setfill('0');
  stream << date.GetMonth() << "-";
  stream << std::setw(2);
  stream << std::setfill('0');
  stream << date.GetDay();
  return stream;
}