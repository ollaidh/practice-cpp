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
  // Наполните полями эту структуру
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  // Реализуйте эту функцию
  return os;
}

struct StopsForBusResponse {
  // Наполните полями эту структуру
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  // Реализуйте эту функцию
  return os;
}

struct AllBusesResponse {
  // Наполните полями эту структуру
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  // Реализуйте эту функцию
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
