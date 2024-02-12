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

int countDaysDifference(Date startDate, Date endDate) {
    struct std::tm start = {0, 0, 0, startDate.day, startDate.month, startDate.year - 1900};  // Starts from 01-01-2000
    struct std::tm end = {0, 0, 0, endDate.day, endDate.month, endDate.year - 1900}; /* July 5, 2004 */
    std::time_t x = std::mktime(&start);
    std::time_t y = std::mktime(&end);
    int difference = std::difftime(y, x) / (60 * 60 * 24) + 1;
    return difference;
}

int dateToIndex(Date date) {
  Date startDate(2000, 1, 1);
  return countDaysDifference(startDate, date);
}

class Budget {
public:
  Budget() : m_earnings(365, 0){}

  void earn(const Date& startDate, const Date& endDate, double amount) {
    int periodDays = countDaysDifference(startDate, endDate);
    double dailyIncome = amount / periodDays;

    for (int i = dateToIndex(startDate); i <= dateToIndex(endDate); i++) {
      m_earnings[i] += dailyIncome;
    }
  }

  double computeIncome(const Date& startDate, const Date& endDate) {
    std::cout << "income!!!"<< "\n";

    std::vector<double>::iterator itStart = m_earnings.begin() + dateToIndex(startDate);
    std::vector<double>::iterator itEnd = itStart + dateToIndex(endDate);
    double result = std::accumulate(itStart, itEnd, 0);
    for (int i = dateToIndex(startDate); i <= dateToIndex(endDate); i ++) {
      std::cout << m_earnings[i] << " ";
    }
    std::cout << std::endl;
    return result;
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

void testTest() {
  AssertEqual(1, 1, "test");
}

void runTests() {
  TestRunner tr;
  tr.RunTest(testTest, "justTest");
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
      std::cout << "HERE!!!"<< "\n";
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

