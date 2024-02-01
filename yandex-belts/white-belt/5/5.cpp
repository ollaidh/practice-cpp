#include <iomanip>
#include <iostream>
#include <istream>
#include <sstream>
#include <exception>
#include <ostream>
#include <stdexcept>
#include <string>
#include <set>
#include <map>
#include <functional>

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

  int DeleteDate(const Date& date) {
    int nDelEvents = 0;
    auto it = m_db.find(date);
    if (it != m_db.end()) {
      nDelEvents = it->second.size();
      m_db.erase(it);
    }
    return nDelEvents;
  }

  std::set<std::string> Find(const Date& date) const {
    auto it = m_db.find(date);
    if (it == m_db.end()) {
      return {};
    }
    return it->second;
  }

  void Print() const {
    for (const auto& [key, value] : m_db) {
      for (const auto &event : value) {
        std::cout << key << " " << event << std::endl;
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

void parseAddCommand(Command& command, std::istream& stream) {
  stream >> command.date;
  stream >> command.event;
}

void parseDelCommand(Command& command, std::istream& stream) {
  stream >> command.date;
  if (stream.peek()) {
    stream >> command.event;
  }
}

void parseFindCommand(Command& command, std::istream& stream) {
  stream >> command.date;
}

void parsePrintCommand(Command& command, std::istream& stream) {
  return;
}

std::map<std::string, std::function<void(Command&, std::istream&)>> commandParsers = {
  {"Add", parseAddCommand},
  {"Del", parseDelCommand},
  {"Find", parseFindCommand},
  {"Print", parsePrintCommand},
};

Command parseCommand(std::string& input) {
  Command command;
  std::stringstream ss{std::move(input)};
  ss >> command.command;
  if (commandParsers.find(command.command) != commandParsers.end()) {
    commandParsers[command.command](command, ss);
  }
  return command;
}


int main() {
  Database db;

  std::set<std::string> validCommands{"Add", "Del", "Find", "Print"};
  std::string input;

  while (std::getline(std::cin, input)) {
    if (input.empty()) {
      continue;
    }
    try {
      Command command = parseCommand(input);

      if (validCommands.find(command.command) == validCommands.end()) {
        std::cout << "Unknown command: " << command.command << std::endl;
        continue;
      }

      if (command.command == "Add") {
        db.AddEvent(command.date, command.event);
      } else if (command.command == "Del") {
        if (command.event.size() != 0) {
          if (db.DeleteEvent(command.date, command.event)) {
            std::cout << "Deleted successfully" << std::endl;
          } else {
            std::cout << "Event not found" << std::endl;
          }
        } else {
          std::cout << "Deleted " << db.DeleteDate(command.date) << " events" << std::endl;
        }
      } else if (command.command == "Find") {
        auto events = db.Find(command.date);
        for (auto ev : events) {
          std::cout << ev << std::endl;
        }
      } else if (command.command == "Print") {
        db.Print();
      }
    } catch (std::exception& ex) {
      std::cout << ex.what() << std::endl;
      continue;
    }
  }
  return 0;
}