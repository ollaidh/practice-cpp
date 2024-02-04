#include <iostream>
#include <vector>
#include <map>
#include <utility>


template<typename T>
T Sqr(T value);

template<typename T>
std::vector<T> Sqr(const std::vector<T>& value);

template<typename K, typename V>
std::map<K, V> Sqr(const std::map<K, V>& value);

template<typename K, typename V>
std::pair<K, V> Sqr(const std::pair<K, V>& value);


template<typename T>
T Sqr(T v) {
  return v * v;
}

template <typename T>
std::vector<T> Sqr(const std::vector<T>& v) {
  std::vector<T> result;
  for (const auto& element : v) {
    result.push_back(Sqr(element));
  }
  return result;
}

template <typename K, typename V>
std::map<K, V> Sqr(const std::map<K, V>& m) {
  std::map<K, V> result;
  for (const auto& [key, value] : m) {
    result[key] = Sqr(value);
  }
  return result;
}

template <typename K, typename V>
std::pair<K, V> Sqr(const std::pair<K, V>& p) {
  return std::make_pair(Sqr(p.first), Sqr(p.second));
}




int main() {
  std::vector<int> v = {1, 2, 3};
  std::cout << "vector:";
  for (int x : Sqr(v)) {
    std::cout << ' ' << x;
  }
  std::cout << std::endl;

  std::map<int, std::pair<int, int>> map_of_pairs = {
    {4, {2, 2}},
    {7, {4, 3}}
  };
  std::cout << "map of pairs:" << std::endl;
  for (const auto& x : Sqr(map_of_pairs)) {
    std::cout << x.first << ' ' << x.second.first << ' ' << x.second.second << std::endl;
  }

  return 0;
}

