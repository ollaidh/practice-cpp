#pragma once

#include <iostream>

class Date {
public:
    Date();

    Date(int year, int month, int day);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

private:
    int m_year;
    int m_month;
    int m_day;
};

bool operator<(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);


std::ostream& operator<<(std::ostream& stream, const Date& date);

Date ParseDate(std::istream& stream);

// tests
void testParseDate();