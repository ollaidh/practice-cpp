#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>

class SortedStrings {
public:
  void AddString(const std::string& s) {
    strings.insert(
        std::lower_bound(strings.begin(), strings.end(), s), s);
  }
  std::vector<std::string> GetSortedStrings() {
    return strings;
  }
private:
  std::vector<std::string> strings;

};

void PrintSortedStrings(SortedStrings& strings) {
  for (const std::string& s : strings.GetSortedStrings()) {
    std::cout << s << " ";
  }
  std::cout << std::endl;
}

int main() {
  SortedStrings strings;

  strings.AddString("first");
  strings.AddString("third");
  strings.AddString("second");
  PrintSortedStrings(strings);

  strings.AddString("second");
  PrintSortedStrings(strings);

  return 0;
}