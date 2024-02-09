#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>


template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  if (range_begin + 2 > range_end) {
    return;
  }

  std::vector<typename RandomIt::value_type> v(range_begin, range_end);

  RandomIt midIt = v.begin() + v.size() / 2;

  MergeSort(v.begin(), midIt);
  MergeSort(midIt, v.end());

  std::merge(v.begin(), midIt, midIt, v.end(), range_begin);
}

int main() {
  std::vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
  return 0;
}