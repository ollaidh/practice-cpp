#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>

struct Date {
  Date(int newYear, int newMonth, int newDay)
  : year(newYear)
  , month(newMonth)
  , day(newDay)
  {}
  int year;
  int month;
  int day;
};

int coundDaysDifference(Date startDate, Date endDate) {
    struct std::tm start = {0, 0, 0, startDate.day, startDate.month, startDate.year - 1900};  // Starts from 01-01-2000
    struct std::tm end = {0, 0, 0, endDate.day, endDate.month, endDate.year - 1900}; /* July 5, 2004 */
    std::time_t x = std::mktime(&start);
    std::time_t y = std::mktime(&end);
    int difference = std::difftime(y, x) / (60 * 60 * 24);
    return difference;
}

int dateToIndex(Date date) {
  Date startDate(2000, 1, 1);
  return coundDaysDifference(startDate, date);
}

class Budget {
public:
  Budget() : m_earnings(365, 0){}

  void earn(Date startDate, Date endDate, double amount) {
    int periodDays = coundDaysDifference(startDate, endDate);
    double dailyIncome = amount / periodDays;

    std::vector<float>::iterator itStart = m_earnings.begin() + dateToIndex(startDate);
    std::vector<float>::iterator itEnd = itStart + dateToIndex(endDate);

    std::fill(itStart, itEnd, dailyIncome);
  }


  double computeIncome(Date startDate, Date endDate);

private:
  std::vector<float> m_earnings;
};

int main() {
  // int nActions;
  // std::cin >> nActions;
  // for (int i = 0; i < nActions; i++) {
  //   continue;
  // }

  Date date(2000, 1,10);
  int index = dateToIndex(date);
  std::cout << index << "\n";





}