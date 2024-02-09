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

  RandomIt oneThirdIt = v.begin() + v.size() / 3;
  RandomIt twoThirdIt = v.begin() + 2 * v.size() / 3;


  MergeSort(v.begin(), oneThirdIt);
  MergeSort(oneThirdIt, twoThirdIt);
  MergeSort(twoThirdIt, v.end());

  std::vector<typename RandomIt::value_type> tempV;

  std::merge(v.begin(), oneThirdIt, oneThirdIt, twoThirdIt, std::back_inserter(tempV));
  std::merge(tempV.begin(), tempV.end(), twoThirdIt, v.end(), range_begin);

}

int main() {
  std::vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
  return 0;
}