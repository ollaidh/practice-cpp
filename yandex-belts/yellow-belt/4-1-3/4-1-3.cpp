#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <string>

std::vector<std::string> SplitIntoWords(const std::string& s) {
  std::vector<std::string> result;

  auto itStart = s.begin();
  while (itStart < s.end()) {
    auto it = find_if(itStart, s.end(),
                                            [](char letter){return letter == ' ';});

    std::string word;
    for (auto i = itStart; i != it; i++) {
      word += *i;
    }
    result.push_back(word);
    itStart = it + 1;
  }
  return result;
}

int main() {
  std::string s = "C Cpp Java Python";

  std::vector<std::string> words = SplitIntoWords(s);
  std::cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      std::cout << "/";
    }
    std::cout << *it;
  }
  std::cout << std::endl;

  return 0;
}