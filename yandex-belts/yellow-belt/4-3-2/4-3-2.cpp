#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
#include <ctime>
#include <map>

#ifdef LOCAL_RUN
#include "yandexTest.h"
#endif

// struct Date {
//   Date()
//   : year(-1)
//   , month(-1)
//   , day(-1)
//   {};
//   Date(int newYear, int newMonth, int newDay)
//   : year(newYear)
//   , month(newMonth)
//   , day(newDay)
//   {}
//   int year;
//   int month;
//   int day;
// };

using Date = std::string;

// bool operator<(const Date& lhs, const Date& rhs) {
//   if (lhs.year != rhs.year) {
//     return lhs.year < rhs.year;
//   }
//   if (lhs.month != rhs.month) {
//     return lhs.month < rhs.month;
//   }
//   return lhs.day < rhs.day;
// }

// Date parseDate(const std::string& date) {
//   Date result;
//   std::stringstream ss{date};
//   ss >> result.year;
//   ss.ignore(1);
//   ss >> result.month;
//   ss.ignore(1);
//   ss >> result.day;
//   return result;
// }

std::pair<Date, int> parseEarnCommand(const std::string& input) {
  std::stringstream ss{input};
  std::string start;
  int amount;
  ss >> start;
  ss >> amount;
  return {start, amount};
}

std::pair<Date, Date> parseCountCommand(const std::string& input) {
  std::stringstream ss{input};
  std::string start;
  std::string end;
  ss >> start;
  ss >> end;
  return {start, end};
}

class Budget {
public:

  void earn(Date& date, unsigned int amount) {
    m_earnings[date] += amount;
    auto itStart = m_earnings.lower_bound(date);
    if (itStart != m_earnings.begin()) {
      itStart->second += std::prev(itStart)->second;
    }
    for (auto i = std::next(itStart); i != m_earnings.end(); i++) {
      i->second += amount;
    }

  }

  int computeIncome(const Date& startDate, const Date& endDate) {
    auto itStart = m_earnings.lower_bound(startDate);
    auto itEnd = m_earnings.upper_bound(endDate);

    if (std::distance(itStart, itEnd) < 0) {
      return 0;
    }

    if (itStart == m_earnings.end() || (itStart == itEnd)) {
      return 0;
    }

    if (itStart == std::prev(itEnd) && itStart != m_earnings.begin()) {
      return itStart->second - std::prev(itStart)->second;
    }

    if (itStart == m_earnings.begin()) {
      return std::prev(itEnd)->second;
    }

    int result = std::prev(itEnd)->second - itStart->second;
    return result;
  }

  int getEarnedByDay(const Date& date) const{
    if (m_earnings.find(date) != m_earnings.end()) {
      return m_earnings.at(date);
    } else {
      return 0;
    }
  }

  std::map<std::string, int> getAllEarnings() const {
    return m_earnings;
  }

private:
  std::map<Date, int> m_earnings;
};




#ifdef LOCAL_RUN


void testBudgetEarn() {
  Budget budget;
  Date date = "2000-1-29";
  budget.earn(date, 20);

  Date earnDay1 = "2000-1-28";
  AssertEqual(budget.getEarnedByDay(earnDay1), 0, "earned 0");
  Date earnDay2 = "2000-1-29";
  AssertEqual(budget.getEarnedByDay(earnDay2), 20, "earned 20");

  budget.earn(date, 5);
  AssertEqual(budget.getEarnedByDay(earnDay2), 25, "earned additional 5");

  date = "2000-2-1";
  budget.earn(date, 10);
  AssertEqual(budget.getEarnedByDay(date), 35, "earned 35");


  Date date0 = "1998-1-3";
  budget.earn(date0, 7);
  AssertEqual(budget.getEarnedByDay(date0), 7, "earned 7");
  AssertEqual(budget.getEarnedByDay(earnDay2), 32, "earned 20");

}

void testBudgetComputeIncome() {
  Budget budget;
  Date date1 = "2000-1-2";
  Date date2 = "2000-1-6";
  Date date3 = "2000-1-3";

  AssertEqual(budget.computeIncome(date1, date2), 0, "Nothing earned yet");
  AssertEqual(budget.computeIncome(date2, date1), 0, "Nothing earned yet");

  budget.earn(date1, 20);

  AssertEqual(budget.computeIncome(date1, date1), 20, "1AAAA");

  budget.earn(date2, 10);
  AssertEqual(budget.computeIncome(date2, date2), 10, "2AAAA");

  budget.earn(date3, 10);
  AssertEqual(budget.computeIncome(date3, date3), 10, "3AAAA");


  Date startDateBefore = "1995-1-1";
  Date endDateBefore = "1997-1-1";
  AssertEqual(budget.computeIncome(startDateBefore, startDateBefore), 0, "Day before all earnings");
  AssertEqual(budget.computeIncome(startDateBefore, endDateBefore), 0, "Interval before all earnings");

  Date startDate1 = "2000-1-1";
  Date endDate1 = "2001-1-2";
  AssertEqual(budget.computeIncome(startDate1, endDate1), 40, "1");

  Date startDate2 = "2000-1-2";
  Date endDate2 = "2000-1-6";
  AssertEqual(budget.computeIncome(startDate2, endDate2), 40, "2");

  Date startDate3 = "2000-1-4";
  Date endDate3 = "2000-1-5";
  AssertEqual(budget.computeIncome(startDate3, endDate3), 0, "Interval between earnings - earned 0");

  AssertEqual(budget.computeIncome(date1, date1), 20, "One day earn");

  Date startDateAfter = "2020-1-1";
  Date endDateAfter = "2021-1-1";
  AssertEqual(budget.computeIncome(startDateAfter, startDateAfter), 0, "Day after all earnings");
  AssertEqual(budget.computeIncome(startDateAfter, endDateAfter), 0, "Interval after all earnings");

  Date date0 = "1998-1-3";
  budget.earn(date0, 7);

  AssertEqual(budget.computeIncome(endDateBefore, endDate1), 47, "1 after adding in begin");
  AssertEqual(budget.computeIncome(date0, startDate1), 7, "2 after adding in begin");
  AssertEqual(budget.computeIncome(date0, date0), 7, "2 after adding in begin");


  AssertEqual(budget.computeIncome(startDateBefore, startDateBefore), 0, "Day before all earnings");
  AssertEqual(budget.computeIncome(startDateBefore, endDateBefore), 0, "Interval before all earnings");
  AssertEqual(budget.computeIncome(startDate3, endDate3), 0, "Interval between earnings - earned 0");

  AssertEqual(budget.computeIncome(date1, date1), 20, "One day earn after adding in begin");
  AssertEqual(budget.computeIncome(startDateAfter, startDateAfter), 0, "Day after all earnings");
  AssertEqual(budget.computeIncome(startDateAfter, endDateAfter), 0, "Interval after all earnings");

  AssertEqual(budget.computeIncome(date3, date3), 10, "One last day - 10");


}


void testBudgetComputeIncome2() {
  Budget budget;
  Date date1 = "2000-1-2";
  Date date2 = "2000-1-6";
  Date date3 = "2000-1-3";

  AssertEqual(budget.computeIncome(date1, date2), 0, "Nothing earned yet");

  budget.earn(date1, 20);
  budget.earn(date2, 10);
  budget.earn(date3, 10);

}


// void testParseEarnCommand() {
//   std::string line = "2000-1-2 22.3";
//   auto [date, amount] = parseEarnCommand(line);
//   AssertEqual(date.year, 2000, "");
//   AssertEqual(date.month, 1, "");
//   AssertEqual(date.day, 2, "");
//   AssertEqual(amount, 22.3, "");
// }

// void testParseCountCommand() {
//   std::string line = "2000-1-2 2001-11-12";
//   auto [dateStart, dateEnd] = parseCountCommand(line);
//   AssertEqual(dateStart.year, 2000, "");
//   AssertEqual(dateStart.month, 1, "");
//   AssertEqual(dateStart.day, 2, "");
//   AssertEqual(dateEnd.year, 2001, "");
//   AssertEqual(dateEnd.month, 11, "");
//   AssertEqual(dateEnd.day, 12, "");

//   line = "2000-1-2";
//   auto [dateStart2, dateEnd2] = parseCountCommand(line);
//   AssertEqual(dateStart2.year, 2000, "");
//   AssertEqual(dateStart2.month, 1, "");
//   AssertEqual(dateStart2.day, 2, "");
//   AssertEqual(dateEnd2.year, -1, "");
//   AssertEqual(dateEnd2.month, -1, "");
//   AssertEqual(dateEnd2.day, -1, "");
// }

void runTests() {
  TestRunner tr;
  tr.RunTest(testBudgetEarn, "earn Budget method: ");
  tr.RunTest(testBudgetComputeIncome, "computeIncome Budget method: ");
  tr.RunTest(testBudgetComputeIncome2, "2 computeIncome Budget method: ");

  // tr.RunTest(testParseEarnCommand, "Parsing Earn input command: ");
  // tr.RunTest(testParseCountCommand, "Parsing Count input command: ");
}

#endif

int main() {
  #ifdef LOCAL_RUN
  runTests();
  #endif

  Budget budget;

  int nEarnActions;
  std::string line;

  std::getline(std::cin, line);
  nEarnActions = std::stoi(line);
  for (int i = 0; i < nEarnActions; i++) {
    std::getline(std::cin, line);
    auto [date, amount] = parseEarnCommand(line);
    budget.earn(date, amount);
  }

  int nCountActions;
  std::getline(std::cin, line);
  nCountActions = std::stoi(line);
  for (int i = 0; i < nCountActions; i++) {
    std::getline(std::cin, line);
    auto [start, end] = parseCountCommand(line);
    if (end.empty()) {
      end = start;
    }
    std::cout.precision(25);
    std::cout << budget.computeIncome(start,end) << "\n";
  }
}

