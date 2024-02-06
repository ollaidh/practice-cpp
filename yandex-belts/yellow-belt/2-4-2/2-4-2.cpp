#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

#ifdef LOCAL_RUN

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
#endif

void TestChangeNameHistory1() {
  Person person;
  person.ChangeLastName(1965, "Sergeeva");
  person.ChangeFirstName(1967, "Polina");
  AssertEqual(person.GetFullName(1964), "Incognito");
  AssertEqual(person.GetFullName(1966), "Sergeeva with unknown first name");
  AssertEqual(person.GetFullName(1968), "Polina Sergeeva");

}

void TestChangeNameHistory2() {
  Person person;
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  AssertEqual(person.GetFullName(1964), "Incognito");
  AssertEqual(person.GetFullName(1966), "Polina with unknown last name");
  AssertEqual(person.GetFullName(1968), "Polina Sergeeva");

  person.ChangeFirstName(1970, "Appolinaria");
  AssertEqual(person.GetFullName(1969), "Polina Sergeeva");
  AssertEqual(person.GetFullName(1970), "Appolinaria Sergeeva");

  person.ChangeLastName(1968, "Volkova");
  AssertEqual(person.GetFullName(1969),"Polina Volkova");
  AssertEqual(person.GetFullName(1970),"Appolinaria Volkova");
}


int main() {
  TestRunner runner;

  runner.RunTest(TestChangeNameHistory1, "TestChangeNameHistory1");
  runner.RunTest(TestChangeNameHistory2, "TestChangeNameHistory2");

  return 0;
}
