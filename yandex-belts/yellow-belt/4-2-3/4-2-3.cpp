#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>


#ifdef LOCAL_RUN

enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};


void PrintStats(std::vector<Person> persons);

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  std::vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}

#endif

void PrintStats(std::vector<Person> persons) {
  std::cout << "Median age = " <<
    ComputeMedianAge(persons.begin(), persons.end()) << "\n";

    auto it = std::partition(persons.begin(), persons.end(),
                                [](Person p){return p.gender == Gender::FEMALE;});
    std::cout << "Median age for females = " <<
    ComputeMedianAge(persons.begin(), it) << "\n";

    it = std::partition(persons.begin(), persons.end(),
                              [](Person p){return p.gender == Gender::MALE;});
    std::cout << "Median age for males = " <<
    ComputeMedianAge(persons.begin(), it) << "\n";

    it = std::partition(persons.begin(), persons.end(),
                              [](Person p){return (p.gender == Gender::FEMALE && p.is_employed);});
    std::cout << "Median age for employed females = " <<
    ComputeMedianAge(persons.begin(), it) << "\n";

    it = std::partition(persons.begin(), persons.end(),
                              [](Person p){return (p.gender == Gender::FEMALE && !p.is_employed);});
    std::cout << "Median age for unemployed females = " <<
    ComputeMedianAge(persons.begin(), it) << "\n";

    it = std::partition(persons.begin(), persons.end(),
                              [](Person p){return (p.gender == Gender::MALE && p.is_employed);});
    std::cout << "Median age for employed males = " <<
    ComputeMedianAge(persons.begin(), it) << "\n";

    it = std::partition(persons.begin(), persons.end(),
                              [](Person p){return (p.gender == Gender::MALE && !p.is_employed);});
    std::cout << "Median age for unemployed males = " <<
    ComputeMedianAge(persons.begin(), it) << "\n";

}

int main() {
  std::vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}