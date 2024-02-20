#include <algorithm>
#include <cstddef>
#include <exception>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

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

std::pair<Date, int> parseEarnCommand(const std::string& input) {
  std::stringstream ss{input};
  std::string start;
  int amount;
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

int countDaysInterval(Date startDate, Date endDate) {
    std::tm start = {0, 0, 0, startDate.day, startDate.month - 1, startDate.year - 1700};
    std::tm end = {0, 0, 0, endDate.day, endDate.month - 1, endDate.year - 1700};
    std::time_t x = std::mktime(&start);
    std::time_t y = std::mktime(&end);
    int interval = std::difftime(y, x) / (60 * 60 * 24) + 1;
    return interval;
}

int dateToIndex(Date date) {
  Date startDate(1700, 1, 1);
  return countDaysInterval(startDate, date);
}

class Budget {
public:
  Budget()
  : m_earnings(1464000, 0)
  , m_accumEarnings(1464000, 0)
  , m_dirty(false)
  {}

  void earn(const Date& date, int amount) {
    int index = dateToIndex(date);
    m_earnings[index] += amount;
    m_dirty = true;
  }

  uint64_t computeIncome(const Date& startDate, const Date& endDate) {
    if (m_dirty) {
      std::partial_sum(m_earnings.begin(), m_earnings.end(), m_accumEarnings.begin());
      m_dirty = false;
    }
    if (endDate < startDate) {
      return 0;
    }
    int startIndex = dateToIndex(startDate);
    int endIndex = dateToIndex(endDate);
    return m_accumEarnings[endIndex] - m_accumEarnings[startIndex - 1];
  }

  uint64_t getEarnedByDay(const Date& date) {
    return m_earnings[dateToIndex(date)];
  }

  uint64_t getAccumEarnedByDay(const Date& date) {
    return m_accumEarnings[dateToIndex(date)];
  }

private:
  std::vector<uint64_t> m_earnings;
  std::vector<uint64_t> m_accumEarnings;
  bool m_dirty;
};


#ifdef LOCAL_RUN

void testBudgetEarn() {
  Budget budget;
  Date date = {2000, 1, 29};
  budget.earn(date, 20);

  Date earnDay1 = {2000, 1, 28};
  AssertEqual(budget.getEarnedByDay(earnDay1), 0, "earned 0");
  Date earnDay2 = {2000, 1, 29};
  AssertEqual(budget.getEarnedByDay(earnDay2), 20, "earned 20");

  budget.earn(date, 20);
  AssertEqual(budget.getEarnedByDay(earnDay2), 40, "earned additional 20");

}


void testBudgetComputeIncome() {
  Budget budget;
  Date date1 = {1700, 1, 1};
  Date date2 = {2000, 1, 1};
  Date date3 = {2000, 1, 6};
  Date date4 = {2000, 1, 10};
  Date date4_1 = {2000, 2, 29};
  Date date5 = {2001, 2, 2};
  Date date6 = {2001, 3, 5};
  Date date7 = {2002, 1, 2};
  Date date8 = {2004, 2, 29};
  Date date9 = {2005, 1, 2};
  Date date10 = {2099, 12, 31};

  AssertEqual(budget.computeIncome(date1, date2), 0, "0");

  budget.earn(date2, 10);

  AssertEqual(budget.computeIncome(date1, date2), 10, "date1 - date2: 10");
  AssertEqual(budget.computeIncome(date3, date4), 0, "date3 - date4: 0");
  AssertEqual(budget.computeIncome(date1, date10), 10, "date1 - date10: 10");

  budget.earn(date2, 10);
  AssertEqual(budget.computeIncome(date1, date2), 20, "date1 - date2: 20");
  AssertEqual(budget.computeIncome(date3, date4), 0, "date3 - date4: 0");
  AssertEqual(budget.computeIncome(date1, date10), 20, "date1 - date10: 20");

  budget.earn(date1, 15);
  AssertEqual(budget.computeIncome(date1, date2), 35, "date1 - date2: 35");
  AssertEqual(budget.computeIncome(date3, date4), 0, "date3 - date4: 0");
  AssertEqual(budget.computeIncome(date1, date10), 35, "date1 - date10: 35");

  budget.earn(date5, 20);
  budget.earn(date6, 20);
  budget.earn(date7, 20);
  AssertEqual(budget.computeIncome(date1, date1), 15, "date1: 15");
  AssertEqual(budget.computeIncome(date2, date2), 20, "date2: 20");
  AssertEqual(budget.computeIncome(date5, date5), 20, "date5: 20");
  AssertEqual(budget.computeIncome(date1, date5), 55, "date1 - date5: 55");
  AssertEqual(budget.computeIncome(date1, date7), 95, "date1 - date7: 95");

  AssertEqual(budget.computeIncome(date8, date9), 0, "date8 - date9: 0");
  AssertEqual(budget.computeIncome(date10, date10), 0, "date10 - date10: 0");

  AssertEqual(budget.computeIncome(date4_1, date4_1), 0, "date4_1 - date4_1: 0");

  AssertEqual(budget.computeIncome(date10, date1), 0, "date10 - date1: 0");
}


void testParseEarnCommand() {
  std::string line = "2000-1-2 22";
  auto [date, amount] = parseEarnCommand(line);
  AssertEqual(date.year, 2000, "");
  AssertEqual(date.month, 1, "");
  AssertEqual(date.day, 2, "");
  AssertEqual(amount, 22, "");
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

