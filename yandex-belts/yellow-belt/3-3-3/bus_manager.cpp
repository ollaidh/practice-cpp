#include "bus_manager.h"

using namespace std;

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    m_buses.push_back(bus);
    for (const auto& stop : stops ) {
        m_stopsForBus[bus].push_back(stop);
        m_busesForStop[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    BusesForStopResponse response;
    if (m_busesForStop.find(stop) != m_busesForStop.end()) {
        response.stop = stop;
        response.buses = m_busesForStop.at(stop);
    }
    return response;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    StopsForBusResponse response;
    response.stops = {};
    if (m_stopsForBus.find(bus) != m_stopsForBus.end()) {
        response.bus = bus;
        for (const auto& stop : m_stopsForBus.at(bus)) {
        response.stopsOrder.push_back(stop);
        response.stops[stop] = m_busesForStop.at(stop);
        }
    }
    return response;
}

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse response;
    response.buses = m_stopsForBus;
    return response;
}
