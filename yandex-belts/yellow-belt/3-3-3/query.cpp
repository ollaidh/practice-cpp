#include <sstream>
#include <map>

#include "query.h"

using namespace std;

std::map<std::string, QueryType> queryCodes{
  {"NEW_BUS", QueryType::NewBus},
  {"BUSES_FOR_STOP", QueryType::BusesForStop},
  {"STOPS_FOR_BUS", QueryType::StopsForBus},
  {"ALL_BUSES", QueryType::AllBuses}
};

istream& operator >> (istream& is, Query& q) {
  string operation_code;
  is >> operation_code;
  q.type = queryCodes[operation_code];

  if (q.type == QueryType::NewBus) {
    is >> q.bus;
    int stop_count;
    is >> stop_count;
    q.stops = {};
    q.stops.reserve(stop_count);
    for (int i = 0; i < stop_count; i++) {
      std::string stop;
      is >> stop;
      q.stops.push_back(std::move(stop));
    }
  } else if (q.type == QueryType::BusesForStop) {
    is >> q.stop;
    q.stops = {};
    q.bus = "";
  } else if (q.type == QueryType::StopsForBus) {
    is >> q.bus;
    q.stops = {};
    q.stop = "";
  }
  return is;
}