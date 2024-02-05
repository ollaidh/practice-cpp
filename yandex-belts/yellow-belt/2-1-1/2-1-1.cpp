#include <set>
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
  cin >> operation_code;
  q.type = queryCodes[operation_code];

  if (q.type == QueryType::NewBus) {
    is >> q.bus;
    int stop_count;
    is >> stop_count;
    q.stops.reserve(stop_count);
    for (int i = 0; i < stop_count; i++) {
      std::string stop;
      is >> stop;
      q.stops.push_back(std::move(stop));
    }
  } else if (q.type == QueryType::BusesForStop) {
    is >> q.stop;
  } else if (q.type == QueryType::StopsForBus) {
    is >> q.bus;
  }
  return is;
}

struct BusesForStopResponse {
  std::string stop;
  std::set<std::string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.stop.size() == 0) {
    os << "No stop" << endl;
  } else {
    for (std::string bus : r.buses) {
      os << bus << " ";
    }
    cout << endl;
  }
  return os;
}

struct StopsForBusResponse {
  std::string bus;
  std::map<std::string, std::set<std::string>> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.bus.size() == 0) {
    cout << "No bus" << endl;
  } else {
    for (const auto& [stop, bus] : r.stops) {
      cout << "Stop " << stop << ": ";
      if (bus.size() == 1) {
        cout << "no interchange";
      } else {
        for (const string& other_bus : bus) {
          if (r.bus != other_bus) {
            cout << other_bus << " ";
          }
        }
      }
      cout << endl;
    }
  }
  return os;
}

struct AllBusesResponse {


};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (buses_to_stops.empty()) {
    cout << "No buses" << endl;
  } else {
    for (const auto& bus_item : buses_to_stops) {
      cout << "Bus " << bus_item.first << ": ";
      for (const string& stop : bus_item.second) {
        cout << stop << " ";
      }
      cout << endl;
    }
  }
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    // Реализуйте этот метод
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    // Реализуйте этот метод
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    // Реализуйте этот метод
  }

  AllBusesResponse GetAllBuses() const {
    // Реализуйте этот метод
  }
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
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
