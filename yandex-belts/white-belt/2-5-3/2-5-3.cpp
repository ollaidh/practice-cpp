#include <iostream>
#include <string>
#include <map>
#include <vector>

class Routes {
    std::map<std::string, std::vector<std::string>> m_buses;
    std::map<std::string, std::vector<std::string>> m_stops;

public:
    void newBus(std::string bus, std::vector<std::string> stops) {
        m_buses[bus] = stops;
        for (std::string stop : stops) {
            m_stops[stop].push_back(bus);
        }
    }

    void const busesForStop(std::string stop) {
        if (m_stops[stop].size() == 0) {
            std::cout << "No stop" << "\n";
        } else {
            for (const auto& bus : m_stops[stop]) {
                std::cout << bus << " ";
            }
            std::cout << "\n";
        }

    }

    void const stopsForBus(std::string bus) {
        if (m_buses[bus].size() == 0) {
            std::cout << "No bus" << "\n";

        } else {
            for (const auto& stop : m_buses[bus]) {
                std::cout << "Stop " << stop << ": ";
                if (m_stops[stop].size() == 1) {
                    std::cout << "no interchange" << "\n";
                } else {
                    for (const auto& curr_bus : m_stops[stop]) {
                        if (curr_bus != bus) {
                            std::cout << curr_bus << " ";
                        }
                    }
                    std::cout << "\n";
                }
            }

        }

    }

    void const allBuses() {
        if (m_buses.size() == 0) {
            std::cout << "No buses" << "\n";

        } else {
            for (const auto& [key, value] : m_buses) {
                std::cout << "Bus " << key << ": ";
                for (const auto& stop : value) {
                    std::cout << stop << " ";
                }
                std::cout << "\n";
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
            routes.busesForStop(std::move(stop));
        } else if (command == "STOPS_FOR_BUS") {
            std::string bus;
            std::cin >> bus;
            routes.stopsForBus(std::move(bus));
        } else {
            routes.allBuses();
        }
    }


    return 0;
}