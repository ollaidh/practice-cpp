#include <set>
#include <sstream>
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;



enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

std::map<std::string, QueryType> queryCodes{
  {"NEW_BUS", QueryType::NewBus},
  {"BUSES_FOR_STOP", QueryType::BusesForStop},
  {"STOPS_FOR_BUS", QueryType::StopsForBus},
  {"ALL_BUSES", QueryType::AllBuses}
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
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

struct BusesForStopResponse {
  std::string stop;
  std::vector<std::string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.stop.size() == 0) {
    os << "No stop";
  } else {
    for (std::string bus : r.buses) {
      os << bus << " ";
    }
    // os << endl;
  }
  return os;
}

struct StopsForBusResponse {
  std::string bus;
  std::vector<std::string> stopsOrder;
  std::map<std::string, std::vector<std::string>> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.bus.size() == 0) {
    os << "No bus";
  } else {
    int nSteps = 0;
    for (const auto& stop : r.stopsOrder) {
      os << "Stop " << stop << ": ";
      if (r.stops.at(stop).size() == 1) {
        os << "no interchange";
      } else {
        for (const string& other_bus : r.stops.at(stop)) {
          if (r.bus != other_bus) {
            os << other_bus << " ";
          }
        }
      }
      if (nSteps != r.stopsOrder.size() - 1) {
        os << endl;
      }
      nSteps ++;
    }
  }
  return os;
}

struct AllBusesResponse {
  std::map<std::string, std::vector<std::string>> buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.buses.empty()) {
    os << "No buses";
  } else {
    int nSteps = 0;
    for (const auto& [bus, stops] : r.buses) {
      int nSteps = 0;
      os << "Bus " << bus << ": ";
      for (const string& stop : stops) {
        os << stop << " ";
      }
      if (nSteps != r.buses.size() - 1) {
        os << endl;
      }
      nSteps++;
    }
  }
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    m_buses.push_back(bus);
    for (const auto& stop : stops ) {
      m_stopsForBus[bus].push_back(stop);
      m_busesForStop[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    BusesForStopResponse response;
    if (m_busesForStop.find(stop) != m_busesForStop.end()) {
      response.stop = stop;
      response.buses = m_busesForStop.at(stop);
    }
    return response;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
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

  AllBusesResponse GetAllBuses() const {
    AllBusesResponse response;
    response.buses = m_stopsForBus;
    return response;
  }

private:
  std::vector<std::string> m_buses;
  std::map<std::string, std::vector<std::string>> m_busesForStop;
  std::map<std::string, std::vector<std::string>> m_stopsForBus;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count = 10;
  Query q;

  // cin >> query_count;

  std::string input = "ALL_BUSES\nBUSES_FOR_STOP Marushkino\nSTOPS_FOR_BUS 32K\nNEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo\nNEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo\nBUSES_FOR_STOP Vnukovo\nNEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo\nNEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo\nSTOPS_FOR_BUS 272\nALL_BUSES";

  stringstream ss{input};

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    ss >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
