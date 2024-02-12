#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>

int dateToIndex(std::string);

class Budget {
public:
  Budget() : m_earnings(365){}

  void earn(std::string startDate, std::string endDate, double amount);
  double computeIncome(std::string startDate, std::string endDate);

private:
  std::vector<float> m_earnings;
};

int main() {
  int nActions;
  std::cin >> nActions;

  for (int i = 0; i < nActions; i++) {
    continue;
  }
}