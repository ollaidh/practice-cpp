#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

template <typename T>
void RemoveDuplicates(std::vector<T>& elements) {
  sort(elements.begin(), elements.end());
  auto it = std::unique(elements.begin(), elements.end());
  elements.erase(it, elements.end());
}

int main() {
  std::vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};
  RemoveDuplicates(v1);
  for (int x : v1) {
    std::cout << x << " ";
  }
  std::cout << std::endl;

  std::vector<std::string> v2 = {"C", "C++", "C++", "C", "C++"};
  RemoveDuplicates(v2);
  for (const std::string& s : v2) {
    std::cout << s << " ";
  }
  std::cout << std::endl;
  return 0;
}