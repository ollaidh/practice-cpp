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
    AssertEqual(1, db.size(), "only record in db");
    Assert(db.find(date1) != db.end(), "added date exists");
    AssertEqual(std::set<std::string>({"event1"}), db[date1], "right event for added date");

}


