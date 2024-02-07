#include "responces.h"

using namespace std;

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.stop.size() == 0) {
    os << "No stop";
  } else {
    for (std::string bus : r.buses) {
      os << bus << " ";
    }
  }
  return os;
}

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