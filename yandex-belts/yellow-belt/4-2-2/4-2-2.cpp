#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>

void outputCombinations(std::vector<int> nums) {
  std::vector<int> curr(nums.size());
  do {
    std::copy(nums.begin(), nums.end(), curr.begin());
    for (auto c : curr) {
      std::cout << c << " ";
    }
    std::cout << std::endl;
  }
  while (std::prev_permutation(nums.begin(), nums.end()));
}

std::vector<int> numberToVector(int number) {
  std::vector<int> result;
  while (number >= 1) {
    result.push_back(number);
    number--;
  }
  return result;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> nums = numberToVector(n);

  outputCombinations(nums);
  return 0;
}