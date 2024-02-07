#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>

struct BusesForStopResponse {
  std::string stop;
  std::vector<std::string> buses;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
  std::string bus;
  std::vector<std::string> stopsOrder;
  std::map<std::string, std::vector<std::string>> stops;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
  std::map<std::string, std::vector<std::string>> buses;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);