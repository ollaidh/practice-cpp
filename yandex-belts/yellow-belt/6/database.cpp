#include "database.h"

#include <iostream>

#include "date.h"

void Database::AddEvent(const Date& date, const std::string& event) {
    m_db[date].insert(event);
}

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

int Database::DeleteDate(const Date& date) {
    int nDelEvents = 0;
    auto it = m_db.find(date);
    if (it != m_db.end()) {
      nDelEvents = it->second.size();
      m_db.erase(it);
    }
    return nDelEvents;
}

std::set<std::string> Database::Find(const Date& date) const {
    auto it = m_db.find(date);
    if (it == m_db.end()) {
      return {};
    }
    return it->second;
}

void Database::Print() const {
    for (const auto& [key, value] : m_db) {
      for (const auto &event : value) {
        std::cout << key << " " << event << std::endl;
      }
    }
}


