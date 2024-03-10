#include "database.h"

#include <iostream>

#include "date.h"

#ifdef LOCAL_RUN
#include "yandexTest.h"
#include "condition_parser.h"
#endif


std::ostream& operator<<(std::ostream& stream, const Entry& entry) {
  stream << entry.date;
  stream << " ";
  stream << entry.event;

  return stream;
}


// add event for specific date
void Database::Add(const Date& date, const std::string& event) {
    m_db[date].insert(event);
}

// find all records for specific date
std::set<std::string> Database::Find(const Date& date) const {
    auto it = m_db.find(date);
    if (it == m_db.end()) {
      return {};
    }
    return it->second;
}

// print all database records
void Database::Print(std::ostream& stream) const {
  for (const auto& [key, value] : m_db) {
    for (const auto &event : value) {
      stream << key << " " << value << std::endl;
    }
  }
}

// get whole database:
std::map<Date, std::set<std::string>> Database::getRecords() {
    return m_db;
}

#ifdef LOCAL_RUN
// tests
void testDatabaseActions() {
    Database database;

    Date date1 = Date(2020, 02, 01);
    database.Add(date1, "event1");
    auto db = database.getRecords();
    AssertEqual(1, db.size(), "only date in db");
    Assert(db.find(date1) != db.end(), "added date exists");
    AssertEqual(std::set<std::string>({"event1"}), db[date1], "right event for added date");

    database.Add(date1, "event11");
    db = database.getRecords();
    AssertEqual(1, db.size(), "still only date in db");
    AssertEqual(std::set<std::string>({"event1", "event11"}), db[date1], "two events for one date");

    AssertEqual(database.Find(date1), std::set<std::string>({"event1", "event11"}), "Find method test");

    Date date2 = Date(2021, 12, 11);
    database.Add(date2, "event2");
    database.Add(date2, "event22");
    database.Add(date2, "event222");

    AssertEqual(database.Find(date2), std::set<std::string>({"event2", "event22", "event222"}),
                "check date exists with right events");

    // Delete event "Event222" of date 2021-12-11
    std::string line = "date == 2021-12-11 AND event == \"event22\"";
    istringstream is(line);
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    int nRemoved = database.RemoveIf(predicate);

    db = database.getRecords();
    AssertEqual(std::set<std::string>({"event2", "event222"}), db[date2], "Delete event test");
    AssertEqual(1, nRemoved, "Number of removed records");

    // Delete all records for date 2021-12-11 and the date becomes empty and is deleted automatically
    line = "date == 2021-12-11";
    istringstream is2(line);
    auto condition2 = ParseCondition(is2);
    auto predicate2 = [condition2](const Date& date, const string& event) {
      return condition2->Evaluate(date, event);
    };
    int nRemoved2 = database.RemoveIf(predicate2);
    AssertEqual(2, nRemoved2, "Removed 2 records");
    db = database.getRecords();
    Assert(db.find(date2) == db.end(), "Deleted all records from day and day itself");

    // Find all records for conditions
    Date date3 = Date(2023, 12, 21);
    database.Add(date3, "event3");
    database.Add(date3, "event33");
    database.Add(date3, "event333");

    line = "date == 2023-12-21";
    istringstream is3(line);
    auto condition3 = ParseCondition(is3);
    auto predicate3 = [condition3](const Date& date, const string& event) {
      return condition3->Evaluate(date, event);
    };
    auto result3 = database.FindIf(predicate3);
    AssertEqual(3, result3.size(), "3 entries found by condition");
    AssertEqual(result3[0].event, "event3", "event3 is found");
    AssertEqual(result3[1].event, "event33", "event33 is found");
    AssertEqual(result3[2].event, "event333", "event333 is found");

}
#endif