#include <algorithm>
#include <cstdlib>
#include <set>
#include <iostream>

using Iter = std::set<int>::const_iterator;

Iter FindNearestElement(const std::set<int>& numbers, int number) {
  if (numbers.empty()) {
    return numbers.end();
  }

  auto lbIt = numbers.lower_bound( number);

  if (lbIt == numbers.end()) {
    return std::prev(lbIt);
  }

  auto valLB = *lbIt;

  if (valLB == number || lbIt == numbers.begin()) {
    return lbIt;
  }

  auto itPrev = std::prev(lbIt);
  auto valPrev = *itPrev;

  if (number - valPrev < valLB - number) {
    return itPrev;
  }
  if (number - valPrev > valLB - number) {
    return lbIt;
  }
  if (valPrev < valLB) {
    return itPrev;
  }
  return lbIt;

}


int main() {
  std::set<int> numbers = {1, 4, 6};
  std::cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << std::endl;

  std::set<int> empty_set;

  std::cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << std::endl;
  return 0;
}