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

struct Date {
  Date()
  : year(-1)
  , month(-1)
  , day(-1)
  {};
  Date(int newYear, int newMonth, int newDay)
  : year(newYear)
  , month(newMonth)
  , day(newDay)
  {}
  int year;
  int month;
  int day;
};

bool operator<(const Date& lhs, const Date& rhs) {
  if (lhs.year != rhs.year) {
    return lhs.year < rhs.year;
  }
  if (lhs.month != rhs.month) {
    return lhs.month < rhs.month;
  }
  return lhs.day < rhs.day;
}

Date parseDate(const std::string& date) {
  Date result;
  std::stringstream ss{date};
  ss >> result.year;
  ss.ignore(1);
  ss >> result.month;
  ss.ignore(1);
  ss >> result.day;
  return result;
}

std::pair<Date, double> parseEarnCommand(const std::string& input) {
  std::stringstream ss{input};
  std::string start;
  double amount;
  ss >> start;
  ss >> amount;
  return {parseDate(start), amount};
}

std::pair<Date, Date> parseCountCommand(const std::string& input) {
  std::stringstream ss{input};
  std::string start;
  std::string end;
  ss >> start;
  ss >> end;
  return {parseDate(start), parseDate(end)};
}

class Budget {
public:
  void earn(const Date& date, double amount) {
    m_earnings[date] += amount;
  }

  double computeIncome(const Date& startDate, const Date& endDate) {
    auto itStart = m_earnings.lower_bound(startDate);
    auto itEnd = m_earnings.upper_bound(endDate);

    if (itStart == m_earnings.end()) {
      return 0;
    }

    if (itStart == std::prev(itEnd)) {
      return itStart->second;
    }

    double result = std::accumulate(itStart, itEnd, 0.0,
            [](double acc, const auto& pair) {
                return acc + pair.second;
            });
    return result;
  }

  double getEarnedByDay(const Date& date) {
    return m_earnings[date];
  }

private:
  std::map<Date, double> m_earnings;
};




#ifdef LOCAL_RUN


void testBudgetEarn() {
  Budget budget;
  Date date = {2000, 1, 29};
  budget.earn(date, 20.2);

  Date earnDay1 = {2000, 1, 28};
  AssertEqual(budget.getEarnedByDay(earnDay1), 0, "earned 0");
  Date earnDay2 = {2000, 1, 29};
  AssertEqual(budget.getEarnedByDay(earnDay2), 20.2, "earned 20.2");

  budget.earn(date, 20.2);
  AssertEqual(budget.getEarnedByDay(earnDay2), 40.4, "earned additional 20.2");

}

void testBudgetComputeIncome() {
  Budget budget;
  Date date1 = {2000, 1, 2};
  Date date2 = {2000, 1, 6};
  Date date3 = {2000, 1, 3};

  budget.earn(date1, 20);
  budget.earn(date2, 10);
  budget.earn(date3, 10);

  Date startDate1 = {2000, 1, 1};
  Date endDate1 = {2001, 1, 2};

  Date startDate2 = {2000, 1, 2};
  Date endDate2 = {2000, 1, 6};

  Date startDate3 = {2000, 1, 4};
  Date endDate3 = {2000, 1, 5};

  AssertEqual(budget.computeIncome(startDate1, endDate1), 40, "1");
  AssertEqual(budget.computeIncome(startDate2, endDate2), 40, "2");
  AssertEqual(budget.computeIncome(startDate3, endDate3), 0, "");
  AssertEqual(budget.computeIncome(date1, date1), 20, "one day earn");

}

void testParseEarnCommand() {
  std::string line = "2000-1-2 22.3";
  auto [date, amount] = parseEarnCommand(line);
  AssertEqual(date.year, 2000, "");
  AssertEqual(date.month, 1, "");
  AssertEqual(date.day, 2, "");
  AssertEqual(amount, 22.3, "");
}

void testParseCountCommand() {
  std::string line = "2000-1-2 2001-11-12";
  auto [dateStart, dateEnd] = parseCountCommand(line);
  AssertEqual(dateStart.year, 2000, "");
  AssertEqual(dateStart.month, 1, "");
  AssertEqual(dateStart.day, 2, "");
  AssertEqual(dateEnd.year, 2001, "");
  AssertEqual(dateEnd.month, 11, "");
  AssertEqual(dateEnd.day, 12, "");

  line = "2000-1-2";
  auto [dateStart2, dateEnd2] = parseCountCommand(line);
  AssertEqual(dateStart2.year, 2000, "");
  AssertEqual(dateStart2.month, 1, "");
  AssertEqual(dateStart2.day, 2, "");
  AssertEqual(dateEnd2.year, -1, "");
  AssertEqual(dateEnd2.month, -1, "");
  AssertEqual(dateEnd2.day, -1, "");
}

void runTests() {
  TestRunner tr;
  tr.RunTest(testBudgetEarn, "earn Budget method: ");
  tr.RunTest(testBudgetComputeIncome, "computeIncome Budget method: ");
  tr.RunTest(testParseEarnCommand, "Parsing Earn input command: ");
  tr.RunTest(testParseCountCommand, "Parsing Count input command: ");
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
    if (end.year == -1) {
      end = start;
    }
    std::cout.precision(25);
    std::cout << budget.computeIncome(start,end) << "\n";
  }
}

