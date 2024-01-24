#include <iostream>
#include <ostream>
#include <string>
#include <map>
#include <vector>

class Routes {
    std::map<std::string, std::vector<std::string>> m_buses;
    std::map<std::string, std::vector<std::string>> m_stops;

public:
    void newBus(std::string bus, std::vector<std::string> stops) {
        for (const std::string& stop : stops) {
            m_stops[stop].push_back(bus);
        }
        m_buses[std::move(bus)] = std::move(stops);
    }

    void printBusesForStop(const std::string& stop, std::ostream& stream) const {
        if (m_stops.find(stop) == m_stops.end()) {
            stream << "No stop" << "\n";
        } else {
            for (auto& bus : m_stops.at(stop)) {
                stream << bus << " ";
            }
            stream << "\n";
        }

    }

    void printStopsForBus(const std::string& bus, std::ostream& stream) const {
        if (m_buses.find(bus) == m_buses.end()) {
            stream << "No bus" << "\n";

        } else {
            for (auto& stop : m_buses.at(bus)) {
                stream << "Stop " << stop << ": ";
                if (m_stops.at(stop).size() == 1) {
                    stream << "no interchange" << "\n";
                } else {
                    for (const auto& currBus : m_stops.at(stop)) {
                        if (currBus != bus) {
                            stream << currBus << " ";
                        }
                    }
                    stream << "\n";
                }
            }

        }

    }

    void printAllBuses(std::ostream& stream) const {
        if (m_buses.size() == 0) {
            stream << "No buses" << "\n";

        } else {
            for (const auto& [key, value] : m_buses) {
                stream << "Bus " << key << ": ";
                for (const auto& stop : value) {
                    stream << stop << " ";
                }
                stream << "\n";
            }
        }
    }

};


int main()
{
    int nOperations;
    std::string command;
    std::cin >> nOperations;

    Routes routes;

    for (int i = 0; i < nOperations; i++) {
        std::cin >> command;
        if (command == "NEW_BUS") {
            std::string bus;
            int counter;
            std::vector<std::string> stops;
            std::cin >> bus;
            std::cin >> counter;
            for (int j = 0; j < counter; j++) {
                std::string stop;
                std::cin >> stop;
                stops.push_back(stop);
            }
            routes.newBus(bus, std::move(stops));
        } else if (command == "BUSES_FOR_STOP") {
            std::string stop;
            std::cin >> stop;
            routes.printBusesForStop(stop, std::cout);
        } else if (command == "STOPS_FOR_BUS") {
            std::string bus;
            std::cin >> bus;
            routes.printStopsForBus(bus, std::cout);
        } else if (command == "ALL_BUSES") {
            routes.printAllBuses(std::cout);
        }
    }


    return 0;
}