#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <set>
#include <map>

#include <gtest/gtest.h>

class Time {
public:
    Time(const int hours, const int minutes) {
        int minutesTotal = minutes + hours * 60;
        m_hours = minutesTotal / 60;
        m_minutes = minutesTotal % 60;
    }

    int hours() const {
        return m_hours;
    }

    int minutes() const {
        return m_minutes;
    }

private:
    int m_hours;
    int m_minutes;
};

std::ostream& operator << (std::ostream& stream, const Time& time) {
    stream << std::setfill('0');
    stream << std::setw(2) << time.hours() << ':' << std::setw(2) << time.minutes();
    return stream;
}

bool operator < (const Time& lhs, const Time& rhs) {
    if (lhs.hours() == rhs.hours())
        return lhs.minutes() < rhs.minutes();
    return lhs.hours() < rhs.hours();
}

bool operator == (const Time& lhs, const Time& rhs) {
    return (lhs.hours() == rhs.hours()) && (lhs.minutes() == rhs.minutes());
}

TEST(streams, Times) {
    Time time(12, 15);
    Time time2(2, 5);
    std::stringstream stream;
    stream << time << std::endl << time2 << std::endl;
    std::string output = stream.str();

    std::string expected = "12:15\n02:05\n";
    ASSERT_EQ(expected, output);
}

template <typename T, typename U>
std::ostream& operator << (std::ostream& stream, const std::pair<T, U>& pair) {
    stream << "{" << pair.first << ", " << pair.second << "}";
    return stream;
}


template <typename T>
void printContainer(std::ostream& stream, const T& container) {
    for (const auto& c: container) {
        stream << c << ", ";
    }
    stream << std::endl;
}

template <typename T, typename U>
std::map<U, T> invertMap(const std::map<T, U>& map) {
    std::map<U, T> result;
    for (const auto& [key, value] : map) {
        result[value] = key;
    }
    return result;
}



TEST(streams, Containers) {
//    std::vector<std::string> numbers = {
//            "one", "two", "three"
//    };
//    std::set<std::string> uniqueNumbers = {
//            "one", "two", "three"
//    };

    std::map<std::string, int> numberIndex = {
            {"one", 1}, {"two", 2}, {"three", 3}
    };

//    printContainer(stream, numbers);
//    printContainer(stream, uniqueNumbers);
//    printContainer(stream, numberIndex);

    auto invertedNumberIndex = invertMap(numberIndex);
//    std::stringstream stream;
    std::map<int, std::string> expectedNumberInv = {
            {1, "one"},
            {2, "two"},
            {3, "three"}
    };
    ASSERT_EQ(expectedNumberInv, invertedNumberIndex);

//    printContainer(std::cout, invertedNumberIndex);

    std::map<std::string, Time> events = {
            {"breakfast", Time(8, 20)},
            {"lunch", Time(13, 0)},
            {"dinner", Time(19, 15)}
    };

//    printContainer(std::cout, events);
    std::map<Time, std::string> expextedEventsInv = {
            {Time(8, 20), "breakfast"},
            {Time(13, 0), "lunch"},
            {Time(19, 15), "dinner"}
    };
    auto eventsIndex = invertMap(events);
    ASSERT_EQ(expextedEventsInv, eventsIndex);
//    printContainer(std::cout, eventsIndex);
}
