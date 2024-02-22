#include <algorithm>
#include <cstdlib>
#include <set>
#include <iostream>

using Iter = std::set<int>::iterator;

Iter FindNearestElement(std::set<int>& numbers, int number) {
  if (numbers.empty()) {
    return numbers.end();
  }

  auto lbIt = lower_bound(numbers.begin(), numbers.end(), number);
  auto itPrev = std::prev(lbIt);
  if (lbIt == numbers.end()) {
    return itPrev;
  }
  if (*lbIt == number || lbIt == numbers.begin()) {
    return lbIt;
  }

  if (number - *itPrev < *lbIt - number) {
    return itPrev;
  }
  if (number - *itPrev > *lbIt - number) {
    return lbIt;
  }
  if (*itPrev < *lbIt) {
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