
#include "airline_ticket.h"

#include "test_runner.h"
#include <algorithm>
#include <numeric>
using namespace std;
bool operator==(const Date & lhs, const Date &rhs)
{
    return std::make_tuple(lhs.year, lhs.month, lhs.day) ==
           std::make_tuple(rhs.year, rhs.month, rhs.day);
}
bool operator<(const Date & lhs, const Date &rhs)
{
    return std::make_tuple(lhs.year, lhs.month, lhs.day) <
           std::make_tuple(rhs.year, rhs.month, rhs.day);
}
std::ostream & operator<<(std::ostream & stream, const Date & date)
{
    stream << date.year << "-" << date.month << "-" << date.day;
    return stream;
}
bool operator==(const Time & lhs, const Time &rhs)
{
    return std::make_tuple(lhs.hours, lhs.minutes) ==
           std::make_tuple(rhs.hours, rhs.hours);
}
bool operator<(const Time & lhs, const Time &rhs)
{
    return std::make_tuple(lhs.hours, lhs.minutes) ==
           std::make_tuple(rhs.hours, rhs.hours);
}
std::ostream & operator<<(std::ostream & stream, const Time & time)
{
    stream << time.hours << "-" << time.minutes;
    return stream;
}

#define UPDATE_FIELD(ticket, field, values)

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}