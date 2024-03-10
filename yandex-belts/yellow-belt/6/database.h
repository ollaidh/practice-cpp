#pragma once

#include <map>
#include <ostream>
#include <set>

#include "date.h"

struct Entry {
    Entry(const Date& new_date, const std::string& new_event)
    : date(new_date)
    , event(new_event)
    {}

    Date date;
    std::string event;
};

std::ostream& operator<<(std::ostream& stream, const Entry& entry);


class Database {
public:
    // add event for specific date
    void Add(const Date& date, const std::string& event);

    // delete all records for which condition is true,
    // count number of deleted
    template<typename Predicate>
    int RemoveIf(Predicate predicate) {
        auto curr_db = m_db;
        int nDeleted = 0;
        for (auto& [date, events] : m_db) {
            for (const auto &event : events) {
                if (predicate(date, event)) {
                    curr_db[date].erase(event);
                    if (curr_db[date].empty()) {
                        curr_db.erase(date);
                    }
                    nDeleted += 1;
                }
            }
        }
        m_db = curr_db;
        return nDeleted;
    }

    // find all records for which condition is true
    // template<typename Predicate>
    // int FindIf(Predicate predicate) {
    //     int nDeleted = 0;
    //     for (auto& [date, events] : m_db) {
    //         for (const auto &event : events) {
    //             if (predicate(date, event)) {
    //                 curr_db[date].erase(event);
    //                 if (curr_db[date].empty()) {
    //                     curr_db.erase(date);
    //                 }
    //                 nDeleted += 1;
    //             }
    //         }
    //     }
    //     m_db = curr_db;
    //     return nDeleted;
    // }

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
