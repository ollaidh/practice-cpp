#include <cstddef>
#include <iostream>
#include <istream>
#include <sstream>
#include <ostream>
#include <string>
#include <vector>
#include <map>

class Planner {
    std::map<int, size_t> daysInMonth {
        {1, 31}, {2, 28}, {3, 31}, {4, 30}, {5, 31}, {6, 30},
        {7, 31}, {8, 31}, {9, 30}, {10, 31}, {11, 30}, {12, 31}
    };

    int m_currentMonth;
    std::vector<std::vector<std::string>> m_tasks;

public:
    Planner() :
        m_currentMonth(1)
    {
        m_tasks.resize(31);
    };

    void addTask(int day, std::string task) {
        m_tasks[day - 1].push_back(task);
    }

    void dumpTasks(int day, std::ostream& stream) {
        stream << m_tasks[day - 1].size() << " ";
        for (auto task : m_tasks[day - 1]) {
            stream << task << " ";
        }
        stream << "\n";
    }

    void nextMonth() {
        if (m_currentMonth == 12) {
            m_currentMonth = 1;
        } else {
            m_currentMonth ++;
        }
        if (m_tasks.size() < daysInMonth[m_currentMonth]) {
            m_tasks.resize(daysInMonth[m_currentMonth]);
        } else if (m_tasks.size() > daysInMonth[m_currentMonth]) {
            int lastDay = m_tasks.size() - 1;
            while (lastDay > daysInMonth[m_currentMonth] - 1) {
                for (auto b : m_tasks[lastDay]) {
                    m_tasks[daysInMonth[m_currentMonth] - 1].push_back(b);
                }
                lastDay --;
            }
        }
        m_tasks.resize(daysInMonth[m_currentMonth]);

    }
};

int main()
{
    Planner planner;
    int nOperations;
    std::cin >>nOperations;

    for (int i = 0; i < nOperations; i ++) {
        std::string action;
        int date;
        std::string task;

        std::cin >> action;
        if (action == "NEXT") {
            planner.nextMonth();
            continue;
        }

        std::cin >> date;
        if (action == "DUMP") {
            planner.dumpTasks(date, std::cout);
            continue;
        }

        std::cin >> task;

        if (action == "ADD") {
            planner.addTask(date, task);
        }


    }

    return 0;
}