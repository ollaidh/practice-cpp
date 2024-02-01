#include <iomanip>
#include <iostream>
#include <sstream>
#include <exception>
#include <ostream>
#include <stdexcept>
#include <string>
#include <set>
#include <map>

bool isValidDay(int day)
{
    return day > 0 && day < 32;
}

bool isValidMonth(int month)
{
    return month > 0 && month < 13;
}

class Date {
public:
    Date()
    {
        m_year = 0;
        m_month = 0;
        m_day = 0;
    }

    Date(int year, int month, int day) : Date()
    {
        if (isValidMonth(month) == false)
            throw std::invalid_argument("Month value is invalid: " + std::to_string(month));
        if (isValidDay(day) == false)
            throw std::invalid_argument("Day value is invalid: " + std::to_string(day));
        m_year = year;
        m_month = month;
        m_day = day;
    }

  int GetYear() const {
    return m_year;
  }
  int GetMonth() const {
    return m_month;
  }
  int GetDay() const {
    return m_day;
  }

private:
  int m_year;
  int m_month;
  int m_day;
};

bool operator<(const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() != rhs.GetYear()) {
    return lhs.GetYear() < rhs.GetYear();
  }
  if (lhs.GetMonth() != rhs.GetMonth()) {
    return lhs.GetMonth() < rhs.GetMonth();
  }
  return lhs.GetDay() < rhs.GetDay();
}

std::istream& operator>>(std::istream& stream, Date& date) {
  std::string line;
    std::istringstream sstream;
    stream >> line;
    sstream.str(line);

    int year, month, day;

    if (!(sstream >> year))
        throw std::runtime_error("Wrong date format: " + line);

    if (sstream.peek() != '-')
        throw std::runtime_error("Wrong date format: " + line);
    sstream.ignore(1);

    if (!(sstream >> month))
        throw std::runtime_error("Wrong date format: " + line);
    if (sstream.peek() != '-')
        throw std::runtime_error("Wrong date format: " + line);
    sstream.ignore(1);

    if (!(sstream >> day))
        throw std::runtime_error("Wrong date format: " + line);
    if (sstream.peek() != EOF)
        throw std::runtime_error("Wrong date format: " + line);

    date = Date(year, month, day);

    return stream;
}


std::ostream& operator<<(std::ostream& stream, const Date& date) {
  stream << std::setw(4);
  stream << std::setfill('0');
  stream << date.GetYear() << "-";
  stream << std::setw(2);
  stream << std::setfill('0');
  stream << date.GetMonth() << "-";
  stream << std::setw(2);
  stream << std::setfill('0');
  stream << date.GetDay();
  return stream;
}

class Database {
public:
  void AddEvent(const Date& date, const std::string& event) {
    m_db[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const std::string& event) {
    if (m_db.contains(date) && m_db[date].contains(event)) {
      m_db[date].erase(event);
      if (m_db[date].size() == 0) {
        m_db.erase(date);
      }
      return true;
    }
    return false;
  }

  int DeleteDate(const Date& date) {
      int nDelEvents = 0;
      if (m_db.contains(date)) {
        nDelEvents = m_db[date].size();
        m_db.erase(date);
      }
      return nDelEvents;
  }

  std::set<std::string> Find(const Date& date) const {
    if (m_db.contains(date)) {
      return m_db.at(date);
    }
    return std::set<std::string>{};
  }

  void Print() const {
    for (const auto& [key, value] : m_db) {
      for (auto event : value) {
        std::cout << key << " " << event << "\n";
      }
    }
  }


private:
  std::map<Date, std::set<std::string>> m_db;
};

struct Command {
  std::string command;
  Date date;
  std::string event;
};

Command parseCommand(std::string& input) {
  Command command;
  std::stringstream ss{std::move(input)};
  ss >> command.command;
  ss >> command.date;
  ss >> command.event;
  return command;
}


int main() {
  Database db;

  std::set<std::string> validCommands{"Add", "Del", "Find", "Print"};
  std::string input;

  while (std::getline(std::cin, input)) {
    try {
      Command command = parseCommand(input);
      if (command.command.size() == 0) {
        continue;
      }
      if (!validCommands.contains(command.command)) {
        std::cout << "Unknown command: " << command.command << "\n";
        continue;
      }

      if (command.command == "Add") {
        db.AddEvent(command.date, command.event);
      } else if (command.command == "Del") {
        if (command.event.size() != 0) {
          if (db.DeleteEvent(command.date, command.event)) {
            std::cout << "Deleted successfully" << "\n";
          } else {
            std::cout << "Event not found" << "\n";
          }
        } else {
          std::cout << "Deleted " << db.DeleteDate(command.date) << " events" << "\n";
        }
      } else if (command.command == "Find") {
        auto events = db.Find(command.date);
        for (auto ev : events) {
          std::cout << ev << "\n";
        }
      } else if (command.command == "Print") {
        db.Print();
      }
    } catch (std::exception& ex) {
      std::cout << ex.what() << "\n";
      continue;
    }






  }




  return 0;
}