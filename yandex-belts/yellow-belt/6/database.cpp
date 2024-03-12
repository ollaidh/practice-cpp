#include "database.h"

#include <algorithm>
#include <iostream>
#include <iterator>

#include "date.h"

#include "test_runner.h"
#include "condition_parser.h"

std::ostream& operator<<(std::ostream& stream, const Entry& entry) {
  stream << entry.date;
  stream << " ";
  stream << entry.event;

  return stream;
}

bool operator!=(const Entry& lhs, const Entry& rhs) {
  if (lhs.date == rhs.date) {
    return rhs.event != lhs.event;
  }
  return true;
}


// add event for specific date
void Database::Add(const Date& date, const std::string& event) {
    for (const auto& ev : m_db[date]) {
      if (ev == event) {
        return;
      }
    }
    m_db[date].push_back(event);
}

Entry Database::Last(const Date& dateLast) const {
    auto dateIt = m_db.upper_bound(dateLast);
    if (dateIt == m_db.begin()) {
        throw std::invalid_argument("No entries!");
    }
    auto date = (std::prev(dateIt))->first;
    return Entry(date, *m_db.at(date).rbegin());

}

// print all database records
void Database::Print(std::ostream& stream) const {
  for (const auto& [date, events] : m_db) {
    for (const auto &event : events) {
      stream << date << " " << event << std::endl;
    }
  }
}

// get whole database:
std::map<Date, std::vector<std::string>> Database::getRecords() {
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
    AssertEqual(std::vector<std::string>({"event1"}), std::vector<std::string>({"event1"}), "right event for added date");

    database.Add(date1, "event11");
    db = database.getRecords();
    AssertEqual(1, db.size(), "still only date in db");
    AssertEqual(std::vector<std::string>({"event1", "event11"}), db[date1], "two events for one date");

    Date date2 = Date(2021, 12, 11);
    database.Add(date2, "event2");
    database.Add(date2, "event22");
    database.Add(date2, "event222");

    // Delete event "event22" of date 2021-12-11
    std::string line = "date == 2021-12-11 AND event == \"event22\"";
    istringstream is(line);
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    int nRemoved = database.RemoveIf(predicate);

    db = database.getRecords();
    AssertEqual(std::vector<std::string>({"event2", "event222"}), db[date2], "Delete event test");
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

    line = "date == 2003-12-21 OR date == 2023-12-21";
    istringstream is4(line);
    auto condition4 = ParseCondition(is4);
    auto predicate4 = [condition3](const Date& date, const string& event) {
      return condition3->Evaluate(date, event);
    };
    auto result4 = database.FindIf(predicate4);
    AssertEqual(3, result4.size(), "3 entries found by condition");

    // Get last entry for certain date:
    auto last1 = database.Last(date3);
    AssertEqual(Entry(date3, "event333"), last1, "check last added");

    Date lastDate2(2023, 1, 1);
    auto last2 = database.Last(lastDate2);
    AssertEqual(Entry(date1, "event11"), last2, "check last added by 2023-01-01");


}
#endif