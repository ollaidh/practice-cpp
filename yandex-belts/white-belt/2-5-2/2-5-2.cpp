#include <iostream>
#include <string>
#include <map>

class Capitals {
    std::map<std::string, std::string> m_capitals;

public:
    void changeCapital(std::string country, std::string newCapital) {
        if (m_capitals[country] == "") {
            std::cout << "Introduce new country " << country << " with capital " << newCapital << "\n";
        } else if (m_capitals[country] == newCapital) {
            std::cout << "Country " << country << " hasn't changed its capital" << "\n";
        } else {
            std::cout << "Country " << country << " has changed its capital from " << m_capitals[country] << " to " << newCapital << "\n";
        }
        m_capitals[country] = newCapital;
    }

    void renameCountry(std::string oldName, std::string newName) {
        if (m_capitals.find(oldName) == m_capitals.end() || m_capitals.find(newName) != m_capitals.end() || oldName == newName) {
            std::cout << "Incorrect rename, skip" << "\n";
        } else {
            std::cout << "Country " << oldName << " with capital " << m_capitals[oldName] << " has been renamed to " << newName << "\n";
            m_capitals[newName] = m_capitals[oldName];
            m_capitals.erase(oldName);
        }
    }

    void aboutCountry(std::string country) {
        if (m_capitals.find(country) == m_capitals.end()) {
            std::cout << "Country " << country << " doesn't exist" << "\n";
        } else {
            std::cout << "Country " << country << " has capital " << m_capitals[country] << "\n";
        }
    }

    void dumpCountries() {
        if (m_capitals.size() == 0) {
            std::cout << "There are no countries in the world" << "\n";
        } else {
            for (const auto& [key, value]: m_capitals) {
                std::cout << key << "/" << value << " ";
            }
        }
    }
};


int main()
{
    int nOperations;
    std::string command;
    std::string parameter1;
    std::string parameter2;
    std::cin >> nOperations;

    Capitals capitals;

    for (int i = 0; i < nOperations; i++) {
        std::cin >> command;
        if (command == "DUMP") {
            capitals.dumpCountries();
        } else if (command == "ABOUT") {
            std::cin >> parameter1;
            capitals.aboutCountry(parameter1);
        } else {
            std::cin >> parameter1;
            std::cin >> parameter2;
            if (command == "RENAME") {
                capitals.renameCountry(parameter1, parameter2);
            } else {
                capitals.changeCapital(parameter1, parameter2);
            }
        }

    }

    return 0;
}