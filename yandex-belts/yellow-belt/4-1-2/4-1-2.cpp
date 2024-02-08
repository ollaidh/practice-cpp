#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <string>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border) {
  std::vector<T> result;
  auto it = std::find_if(elements.begin(), elements.end(), [border](const T& element){
                                                                                return element > border;
                                                                              });
  for (auto i = it; i != elements.end(); i++) {
    result.push_back(*i);
  }
  return result;
}

int main() {
  for (int x : FindGreaterElements(std::set<int>{1, 5, 7, 8}, 5)) {
    std::cout << x << " ";
  }
  std::cout << std::endl;

  std::string to_find = "Python";
  std::cout << FindGreaterElements(std::set<std::string>{"C", "C++"}, to_find).size() << std::endl;
  return 0;
}