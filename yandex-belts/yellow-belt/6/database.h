#pragma once

#include <iterator>
#include <map>
#include <ostream>
#include <set>
#include <vector>

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

bool operator!=(const Entry& lhs, const Entry& rhs);

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
                    for (auto it = curr_db[date].begin(); it != curr_db[date].end(); it++) {
                        if (*it == event) {
                            curr_db[date].erase(it);
                            break;
                        }
                    }
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
    template<typename Predicate>
    std::vector<Entry> FindIf(Predicate predicate) const{
        std::vector<Entry> entries;
        for (auto& [date, events] : m_db) {
            for (const auto &event : events) {
                if (predicate(date, event)) {
                    entries.push_back(Entry(date, event));
                }
            }
        }
        return entries;
    }

    // find last record for date (equal or earlier)
    Entry Last(Date dateLast) const;

    // print all database records
    void Print(std::ostream& stream) const;

    // get whole database:
    std::map<Date, std::vector<std::string>> getRecords();

private:
    std::map<Date, std::vector<std::string>> m_db;
};

// tests
void testDatabaseActions();
