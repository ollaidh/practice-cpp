#include <__chrono/duration.h>
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

int countDaysInterval(Date startDate, Date endDate) {
    std::tm start = {0, 0, 0, startDate.day, startDate.month - 1, startDate.year - 1900};
    std::tm end = {0, 0, 0, endDate.day, endDate.month - 1, endDate.year - 1900};
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
  Budget() : m_earnings(1464000, 0){}

  void earn(const Date& date, double amount) {
    int index = dateToIndex(date);
    m_earnings[index] += amount;
  }

  double computeIncome(const Date& startDate, const Date& endDate) {
    auto itStart = m_earnings.begin() + dateToIndex(startDate);
    auto itEnd = m_earnings.begin() + dateToIndex(endDate);

    double result = std::accumulate(itStart, itEnd + 1, 0.0);
    return result;
  }

  double getEarnedByDay(const Date& date) {
    return m_earnings[dateToIndex(date)];
  }

private:
  std::vector<double> m_earnings;
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
  Date endDate1 = {2000, 1, 2};

  Date startDate2 = {2000, 1, 2};
  Date endDate2 = {2000, 1, 6};

  Date startDate3 = {2000, 1, 4};
  Date endDate3 = {2000, 1, 5};

  AssertEqual(budget.computeIncome(startDate1, endDate1), 20, "");
  AssertEqual(budget.computeIncome(startDate2, endDate2), 40, "");
  AssertEqual(budget.computeIncome(startDate3, endDate3), 0, "");
  AssertEqual(budget.computeIncome(endDate1, endDate1), 20, "one day earn");

}

void testParseEarnCommand() {
  std::string line = "2000-1-2 22.3";
  auto [date, amount] = parseEarnCommand(line);
  AssertEqual(date.year, 2000, "");
  AssertEqual(date.month, 1, "");
  AssertEqual(date.day, 2, "");
  AssertEqual(amount, 22.3, "");
}
//   line = "ComputeIncome 2000-1-1";
//   command = parseCommand(line);
//   AssertEqual(command.action, "ComputeIncome", "");
//   AssertEqual(command.startDate.year, 2000, "");
//   AssertEqual(command.startDate.month, 1, "");
//   AssertEqual(command.startDate.day, 1, "");
//   AssertEqual(command.endDate.year, -1, "");
//   AssertEqual(command.endDate.month, -1, "");
//   AssertEqual(command.endDate.day, -1, "");

// }

void runTests() {
  TestRunner tr;
  // tr.RunTest(testCountDaysInterval, "testCountDaysInterval function: ");
  // tr.RunTest(testParseDate, "testParseDate function: ");
  tr.RunTest(testBudgetEarn, "earn Budget method: ");
  tr.RunTest(testBudgetComputeIncome, "computeIncome Budget method: ");
  tr.RunTest(testParseEarnCommand, "Parsing Earn input command: ");

}

#endif

int main() {
  #ifdef LOCAL_RUN
  runTests();
  #endif

  int nActions;
  // std::cin >> nActions;
  std::string action;
  std::string startDate;
  std::string endDate;
  double amount;
  Budget budget;
  std::string line;
  std::getline(std::cin, line);
  nActions = std::stoi(line);
  // Command command;

  // for (int i = 0; i < nActions; i++) {
  //   std::getline(std::cin, line);
  //   command = parseCommand(line);

  //   if (command.action == "Earn") {
  //     budget.earn(command.startDate, command.endDate, command.amount);
  //   } else if (command.action == "ComputeIncome") {
  //     // std::cout << "YEAR: " << command.endDate.year << "\n";
  //     if (command.endDate.year == -1) {
  //       command.endDate = command.startDate;
  //     }
  //     std::cout.precision(25);
  //     std::cout << budget.computeIncome(command.startDate,command.endDate) << "\n";
  //   }
  // }

}

