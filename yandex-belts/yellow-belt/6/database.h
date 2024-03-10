#pragma once

#include <map>
#include <ostream>
#include <set>

#include "date.h"

class Database {
public:
    // add event for specific date
    void Add(const Date& date, const std::string& event);

    // delete record if condition is true
    template<typename Predicate>
    bool RemoveIf(Predicate predicate) {
        for (auto& [date, events] : m_db) {
            for (const auto &event : events) {
                if (predicate(date, event)) {
                    events.erase(event);
                    if (events.empty()) {
                        m_db.erase(date);
                    }
                }
            }
        }
    }

    // delete all events for specific date and date itself
    int DeleteDate(const Date& date);

    // find all records for specific date
    std::set<std::string> Find(const Date& date) const;

    // print all database records
    void Print(std::ostream& stream) const;

    // get whole database:
    std::map<Date, std::set<std::string>> getRecords();

private:
    std::map<Date, std::set<std::string>> m_db;
};

// tests
void testDatabaseActions();
