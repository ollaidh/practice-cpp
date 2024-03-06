#include "database.h"

#include <iostream>

#include "date.h"

#ifdef LOCAL_RUN
#include "yandexTest.h"
#endif

// add event for specific date
void Database::AddEvent(const Date& date, const std::string& event) {
    m_db[date].insert(event);
}

// delete event for specific date
bool Database::DeleteEvent(const Date& date, const std::string& event) {
    auto itDate = m_db.find(date);
    if (itDate == m_db.end()) {
      return false;
    }
    auto itEvent = itDate->second.find(event);
    if (itEvent == itDate->second.end()) {
      return false;
    }
    itDate->second.erase(event);
    if (itDate->second.empty()) {
      m_db.erase(itDate);
    }
    return true;
}

// delete all events for specific date and date itself
int Database::DeleteDate(const Date& date) {
    int nDelEvents = 0;
    auto it = m_db.find(date);
    if (it != m_db.end()) {
      nDelEvents = it->second.size();
      m_db.erase(it);
    }
    return nDelEvents;
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
void Database::Print() const {
    for (const auto& [key, value] : m_db) {
      for (const auto &event : value) {
        std::cout << key << " " << event << std::endl;
      }
    }
}

// get whole database:
std::map<Date, std::set<std::string>> Database::getRecords() {
    return m_db;
}

// tests
void testDatabaseActions() {
    Database database;

    Date date1 = Date(2020, 02, 01);
    database.AddEvent(date1, "event1");
    auto db = database.getRecords();
    AssertEqual(1, db.size(), "only date in db");
    Assert(db.find(date1) != db.end(), "added date exists");
    AssertEqual(std::set<std::string>({"event1"}), db[date1], "right event for added date");

    database.AddEvent(date1, "event11");
    db = database.getRecords();
    AssertEqual(1, db.size(), "still only date in db");
    AssertEqual(std::set<std::string>({"event1", "event11"}), db[date1], "two events for one date");

    AssertEqual(database.Find(date1), std::set<std::string>({"event1", "event11"}), "Find method test");

    Date date2 = Date(2021, 12, 11);
    database.AddEvent(date2, "event2");
    database.AddEvent(date2, "event22");
    database.AddEvent(date2, "event222");
    Date date3 = Date(2022, 12, 21);

    AssertEqual(database.Find(date2), std::set<std::string>({"event2", "event22", "event222"}),
                "check date exists with right events");
    database.DeleteEvent(date2, "event22");
    db = database.getRecords();
    AssertEqual(std::set<std::string>({"event2", "event222"}), db[date2], "Delete event test");

    database.DeleteDate(date2);
    db = database.getRecords();
    Assert(db.find(date2) == db.end(), "Delete date test");

}


