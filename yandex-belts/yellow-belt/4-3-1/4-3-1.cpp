#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>

#ifdef LOCAL_RUN
#include "yandexTest.h"
#endif

struct Date {
  Date(){};
  Date(int newYear, int newMonth, int newDay)
  : year(newYear)
  , month(newMonth)
  , day(newDay)
  {}
  int year;
  int month;
  int day;
};

int countDaysInterval(Date startDate, Date endDate) {
    struct std::tm start = {0, 0, 0, startDate.day, startDate.month - 1, startDate.year - 1900};
    struct std::tm end = {0, 0, 0, endDate.day, endDate.month - 1, endDate.year - 1900};
    std::time_t x = std::mktime(&start);
    std::time_t y = std::mktime(&end);
    int interval = std::difftime(y, x) / (60 * 60 * 24) + 1;
    return interval;
}

int dateToIndex(Date date) {
  Date startDate(2000, 1, 1);
  return countDaysInterval(startDate, date);
}

class Budget {
public:
  Budget() : m_earnings(365, 0){}

  void earn(const Date& startDate, const Date& endDate, double amount) {
    int periodDays = countDaysInterval(startDate, endDate);
    double dailyIncome = amount / periodDays;

    for (int i = dateToIndex(startDate); i <= dateToIndex(endDate); i++) {
      m_earnings[i] += dailyIncome;
    }
  }

  double computeIncome(const Date& startDate, const Date& endDate) {
    std::vector<double>::iterator itStart = m_earnings.begin() + dateToIndex(startDate);
    std::vector<double>::iterator itEnd = m_earnings.begin() + dateToIndex(endDate);
    double result = std::accumulate(itStart, itEnd + 1, 0);
    return result;
  }

  double getEarnedByDay(const Date& date) {
    return m_earnings[dateToIndex(date)];
  }

private:
  std::vector<double> m_earnings;
};

Date parseDate(std::string& date) {
  Date result;
  std::stringstream ss{date};
  ss >> result.year;
  ss.ignore(1);
  ss >> result.month;
  ss.ignore(1);
  ss >> result.day;
  return result;
}

#ifdef LOCAL_RUN

void testParseDate() {
  std::string currDate = "2000-11-5";
  Date expected = Date(2000, 11, 5);
  Date result = parseDate(currDate);
  AssertEqual(expected.year, result.year, "year");
  AssertEqual(expected.month, result.month, "month");
  AssertEqual(expected.day, result.day, "day");

}

void testCountDaysInterval() {
  Date startDate(2022, 12, 12);
  Date endDate(2022, 12, 16);
  AssertEqual(5, countDaysInterval(startDate, endDate), "2022-12-12 : 2022-12-16");

  startDate = {2020, 2, 27};
  endDate = {2020, 3, 5};
  AssertEqual(8, countDaysInterval(startDate, endDate), "2020-02-27 : 2020-03-05");

  startDate = {2021, 2, 27};
  endDate = {2021, 3, 5};
  AssertEqual(7, countDaysInterval(startDate, endDate), "2021-02-27 : 2021-03-05");

  startDate = {2020, 2, 1};
  endDate = {2020, 2, 1};
  AssertEqual(1, countDaysInterval(startDate, endDate), "2020-02-27 : 2020-03-05");
}

void testBudgetEarn() {
  Budget budget;
  Date startDate = {2000, 1, 29};
  Date endDate = {2000, 2, 2};
  budget.earn(startDate, endDate, 100);

  Date earnDay1 = {2000, 1, 28};
  AssertEqual(budget.getEarnedByDay(earnDay1), 0, "earned 0");
  Date earnDay2 = {2000, 1, 29};
  AssertEqual(budget.getEarnedByDay(earnDay2), 20, "earned 20");
  Date earnDay3 = {2000, 2, 2};
  AssertEqual(budget.getEarnedByDay(earnDay3), 20, "earned 20");
  Date earnDay4 = {2000, 2, 3};
  AssertEqual(budget.getEarnedByDay(earnDay4), 0, "earned 0");

  startDate = {2000, 2, 1};
  endDate = {2000, 2, 4};
  budget.earn(startDate, endDate, 8);
  Date earnDay5 = {2000, 2, 1};
  AssertEqual(budget.getEarnedByDay(earnDay5), 22, "add aother 2 earned for earlier 20");
  Date earnDay6 = {2000, 2, 2};
  AssertEqual(budget.getEarnedByDay(earnDay6), 22, "add aother 2 earned for earlier 20");
  Date earnDay7 = {2000, 2, 3};
  AssertEqual(budget.getEarnedByDay(earnDay7), 2, "earned 22");

  startDate = {2001, 2, 1};
  endDate = {2001, 2, 4};
  budget.earn(startDate, endDate, 10);
  Date earnDay8 = {2001, 2, 1};
  AssertEqual(budget.getEarnedByDay(earnDay8), 2.5, "earned 2.5");

}

void testBudgetComputeIncome() {
  Budget budget;
  Date startDate = {2000, 1, 29};
  Date endDate = {2000, 2, 2};
  budget.earn(startDate, endDate, 100);

  double result = budget.computeIncome(startDate, endDate);
  AssertEqual(result, 100, "the same period as earned");
  result = budget.computeIncome(startDate, startDate);
  AssertEqual(result, 20, "earned for one day");



  Date startDate1 = {2020, 1, 29};
  Date endDate1 = {2020, 2, 2};
  result = budget.computeIncome(startDate1, endDate1);
  AssertEqual(result, 0, "nothing earned for this period");

}

void runTests() {
  TestRunner tr;
  tr.RunTest(testCountDaysInterval, "testCountDaysInterval function: ");
  tr.RunTest(testParseDate, "testParseDate function: ");
  tr.RunTest(testBudgetEarn, "earn Budget method: ");
  tr.RunTest(testBudgetComputeIncome, "computeIncome Budget method: ");
}

#endif

int main() {
  #ifdef LOCAL_RUN
  runTests();
  #endif

  int nActions;
  std::cin >> nActions;
  std::string action;
  std::string startDate;
  std::string endDate;
  double amount;
  Budget budget;

  for (int i = 0; i < nActions; i++) {
    std::cin >> action;
    std::cin >> startDate;

    if (std::cin >> endDate) {
      std::cout << endDate << "\n";
    } else {
      endDate = startDate;
      std::cout << "HERE!";
    }

    if (action == "Earn") {
      std::cin >> amount;
      budget.earn(parseDate(startDate), parseDate(endDate), amount);
    } else if (action == "ComputeIncome") {
      std::cout.precision(25);
      std::cout << budget.computeIncome(parseDate(startDate), parseDate(endDate)) << "\n";
    }
  }

}

