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

class Person {
public:
  void ChangeFirstName(int year, const std::string& first_name) {
    names[year] = first_name;
  }

  void ChangeLastName(int year, const std::string& last_name) {
    lastNames[year] = last_name;
  }

  std::string GetFullName(int year) {
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



  std::string GetFullNameWithHistory(int year) {
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
  std::map<int, std::string, std::greater<>> names;
  std::map<int, std::string, std::greater<>> lastNames;


};

int main() {
  Person person;

  // person.ChangeFirstName(1965, "Polina");
  // person.ChangeFirstName(1970, "Izya");
  // person.ChangeFirstName(1970, "Izya");
  // person.ChangeFirstName(1975, "Naoko");
  // person.ChangeFirstName(1980, "Gloria");

  // for (int year : {1990}) {
  //   std::cout << person.GetFullNameWithHistory(year) << std::endl;
  // }


  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    std::cout << person.GetFullNameWithHistory(year) << std::endl;
  }

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    std::cout << person.GetFullNameWithHistory(year) << std::endl;
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    std::cout << person.GetFullNameWithHistory(year) << std::endl;
  }

  person.ChangeFirstName(1990, "Polina");
  person.ChangeLastName(1990, "Volkova-Sergeeva");
  std::cout << person.GetFullNameWithHistory(1990) << std::endl;

  person.ChangeFirstName(1966, "Pauline");
  std::cout << person.GetFullNameWithHistory(1966) << std::endl;

  person.ChangeLastName(1960, "Sergeeva");
  std::cout << person.GetFullNameWithHistory(1960) << std::endl;
  std::cout << person.GetFullNameWithHistory(1967) << std::endl;

  person.ChangeLastName(1961, "Ivanova");
  std::cout << person.GetFullNameWithHistory(1967) << std::endl;

  return 0;

}