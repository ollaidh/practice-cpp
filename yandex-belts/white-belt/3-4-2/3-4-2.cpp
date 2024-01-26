#include <functional>
#include <iostream>
#include <string>
#include <map>

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
private:
  std::map<int, std::string, std::greater<>> names;
  std::map<int, std::string, std::greater<>> lastNames;

};

int main() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    std::cout << person.GetFullName(year) << std::endl;
  }

  // person.ChangeFirstName(1970, "Appolinaria");
  // for (int year : {1969, 1970}) {
  //   std::cout << person.GetFullName(year) << std::endl;
  // }

  // person.ChangeLastName(1968, "Volkova");
  // for (int year : {1969, 1970}) {
  //   std::cout << person.GetFullName(year) << std::endl;
  // }

  return 0;
}