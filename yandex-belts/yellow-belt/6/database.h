#pragma once

#include <map>
#include <set>

#include "date.h"

class Database {
public:
    // add event for specific date
    void Add(const Date& date, const std::string& event);

    // delete event for specific date
    bool DeleteEvent(const Date& date, const std::string& event);

    // delete all events for specific date and date itself
    int DeleteDate(const Date& date);

    // find all records for specific date
    std::set<std::string> Find(const Date& date) const;

    // print all database records
    void Print() const;

    // get whole database:
    std::map<Date, std::set<std::string>> getRecords();

private:
    std::map<Date, std::set<std::string>> m_db;
};

// tests
void testDatabaseActions();
