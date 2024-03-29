#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <memory>

#include "date.h"
#include "database.h"
#include "condition_parser.h"
#include "node.h"
#include "condition_parser.h"
#include "test_runner.h"


using namespace std;

string ParseEvent(istream& is) {
    // is.ignore(1);
    while (is.peek() == ' ') {
      is.ignore(1);
    }
    std::string event;

    getline(is, event, '\n');

    while (event[-1] == ' ') {
      event.pop_back();
    }

    // std::cout << event <<  "/" << "\n";
    return event;
}

void TestAll();

int main() {
  TestAll();

  Database db;

  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    }

    else if (command == "Print") {
      db.Print(cout);
    }

    else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    }

    else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    }

    else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    }

    else if (command.empty()) {
      continue;
    }

    else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    // AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    std::vector<std::string> expected{"first event  ", "second event"};
    AssertEqual(expected[0], events[0], "Parse multiple events");
    AssertEqual(expected[1], events[1], "Parse multiple events");
  }
}

void TestAll() {
  TestRunner tr;

  #ifdef LOCAL_RUN
  tr.RunTest(testDatabaseActions, "database actions (database.cpp)");

  istringstream is("event");
  ParseEvent(is);

  istringstream is1("  event");
  ParseEvent(is1);
  #endif

  tr.RunTest(TestParseEvent, "TestParseEvent");
  // tr.RunTest(TestParseCondition, "TestParseCondition");
}
