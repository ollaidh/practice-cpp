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

int dateToIndex(Date date) {
    struct std::tm startDate = {0, 0, 0, 1, 1, 100};  // Starts from 01-01-2000
    struct std::tm currDate = {0, 0, 0, date.day, date.month, date.year - 1900}; /* July 5, 2004 */
    std::time_t x = std::mktime(&startDate);
    std::time_t y = std::mktime(&currDate);
    int difference = std::difftime(y, x) / (60 * 60 * 24);
    return difference;
}

class Budget {
public:
  Budget() : m_earnings(365){}

  void earn(Date startDate, Date endDate, double amount);
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