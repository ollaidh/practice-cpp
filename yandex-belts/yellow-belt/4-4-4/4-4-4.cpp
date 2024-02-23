#include <algorithm>
#include <iostream>
#include <vector>

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const std::string& prefix) {
        auto len = prefix.size();
        std::cout << (int)prefix[5] << std::endl;
      auto result = std::equal_range(range_begin,
                                     range_end, prefix,
                                     [prefix, len](const std::string& lhs, const std::string& rhs)
      {
        return std::lexicographical_compare(lhs.begin(), lhs.begin() + len,
                                    rhs.begin(), rhs.begin() + len);
      });

      return result;
}


int main() {
  const std::vector<std::string> sorted_strings = {"m", "moscow", "motovilikha", "murmansk", "puzino"};

  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  std::cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << std::endl;

  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  std::cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << std::endl;

  const auto la_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "la");
  std::cout << (la_result.first - begin(sorted_strings)) << " " <<
      (la_result.second - begin(sorted_strings)) << std::endl;

  const auto w_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "w");
  std::cout << (w_result.first - begin(sorted_strings)) << " " <<
      (w_result.second - begin(sorted_strings)) << std::endl;

  const auto m_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "m");
  std::cout << (m_result.first - begin(sorted_strings)) << " " <<
      (m_result.second - begin(sorted_strings)) << std::endl;

  return 0;
}