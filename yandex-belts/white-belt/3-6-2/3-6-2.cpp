#include <functional>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <assert.h>

  std::vector<std::string> getChangesSequence(const std::map<int, std::string, std::greater<>>& sequence,
                                              int year)
  {
    auto start = sequence.lower_bound(year);
    std::vector<std::string> result;
    for( auto it = start; it != sequence.end(); ++it ) {
      if (!result.empty() && result.back() == it->second)
        continue;
      result.push_back(it->second);
    }
    return result;
  }

  std::string historyString(const std::vector<std::string>& v) {
    assert(!v.empty());
    if (v.size() == 1) {
      return v[0];
    }
    std::string result = v[0] + " (";
    for (int i = 1; i < v.size() - 1; i ++) {
      result += (v[i] + ", ");
    }
    result += v.back();
    result += ")";
    return result;
  }

class Person {
public:
  Person(std::string nameOfBirth, std::string lastNameOfBirth, int yearOfBirth) {
    names[yearOfBirth] = nameOfBirth;
    lastNames[yearOfBirth] = lastNameOfBirth;
    m_yearOfBirth = yearOfBirth;
  }

  void ChangeFirstName(int year, const std::string& first_name) {
    if (year >= m_yearOfBirth) {
      names[year] = first_name;
    }
  }

  void ChangeLastName(int year, const std::string& last_name) {
    if (year >= m_yearOfBirth) {
      lastNames[year] = last_name;
    }
  }

  std::string GetFullName(int year) const {
    if (year < m_yearOfBirth) {
      return "No person";
    }
    auto name = names.lower_bound(year);
    auto surname = lastNames.lower_bound(year);

    if (name == names.end() && surname == lastNames.end()) {
      return "Incognito";
    }

    if (name == names.end()) {
      return surname->second + " with unknown first name";
    }

    if (surname == lastNames.end()) {
      return name->second + " with unknown last name";
    }

    return name->second + " " + surname->second;
  }

  std::string GetFullNameWithHistory(int year) const {
    if (year < m_yearOfBirth) {
      return "No person";
    }
    auto namesHistory = getChangesSequence(names, year);
    auto lastNamesHistory = getChangesSequence(lastNames, year);

    if (namesHistory.empty() && lastNamesHistory.empty()) {
      return "Incognito";
    }

    if (namesHistory.empty()) {
      return historyString(lastNamesHistory) + " with unknown first name";
    }

    if (lastNamesHistory.empty()) {
      return historyString(namesHistory) + " with unknown last name";
    }

    return historyString(namesHistory) + " " + historyString(lastNamesHistory);
  }

private:
  int m_yearOfBirth;
  std::map<int, std::string, std::greater<>> names;
  std::map<int, std::string, std::greater<>> lastNames;
};

int main() {
  return 0;
}