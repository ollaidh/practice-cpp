#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <utility>


template <typename K, typename V>
V& GetRefStrict(std::map<K, V>& m, K key) {
  auto it = m.find(key);
  if (it == m.end()) {
    throw std::runtime_error("No key");
  }
  return it->second;
}


int main() {
  std::map<int, std::string> m = {{0, "value"}};
  std::string& item = GetRefStrict(m, 0);
  item = "newvalue";
  std::cout << m[0] << std::endl; // выведет newvalue

  return 0;
}

