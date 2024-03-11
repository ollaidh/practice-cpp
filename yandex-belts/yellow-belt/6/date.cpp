#include "date.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#ifdef LOCAL_RUN
#include "yandexTest.h"
#endif

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

bool operator!=(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() != rhs.GetYear()) {
        return true;
    }
    if (lhs.GetMonth() != rhs.GetMonth()) {
        return true;
    }
    return lhs.GetDay() != rhs.GetDay();
}

bool operator==(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() != rhs.GetYear()) {
        return false;
    }
    if (lhs.GetMonth() != rhs.GetMonth()) {
        return false;
    }
    return lhs.GetDay() == rhs.GetDay();
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

// parse date from string into Date object
Date ParseDate(std::istream& stream) {
    int year, month, day;

    if (!(stream >> year))
        throw std::runtime_error("Wrong date format1");

    if (stream.peek() != '-')
        throw std::runtime_error("Wrong date format2");
    stream.ignore(1);

    if (!(stream >> month))
        throw std::runtime_error("Wrong date format3");
    if (stream.peek() != '-')
        throw std::runtime_error("Wrong date format4");
    stream.ignore(1);

    if (!(stream >> day))
        throw std::runtime_error("Wrong date format5");

    return Date(year, month, day);
}

// tests
// void testParseDate() {
//     std::string input1 = "2020-01-12";
//     Date expectedDate1 = Date(2020, 1, 12);
//     Date result1 = ParseDate(input1);
//     AssertEqual(expectedDate1, result1, "Full format date '2020-01-12'");

//     std::string input2 = "2020-1-2";
//     Date expectedDate2 = Date(2020, 1, 2);
//     Date result2 = ParseDate(input2);
//     AssertEqual(expectedDate2, result2, "cut format date '2020-1-2'");
// }