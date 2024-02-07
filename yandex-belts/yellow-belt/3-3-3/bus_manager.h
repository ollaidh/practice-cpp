#pragma once

#include "responces.h"

class BusManager {
public:
  void AddBus(const std::string& bus, const std::vector<std::string>& stops);

  BusesForStopResponse GetBusesForStop(const std::string& stop) const;

  StopsForBusResponse GetStopsForBus(const std::string& bus) const;

  AllBusesResponse GetAllBuses() const;

private:
  std::vector<std::string> m_buses;
  std::map<std::string, std::vector<std::string>> m_busesForStop;
  std::map<std::string, std::vector<std::string>> m_stopsForBus;
};