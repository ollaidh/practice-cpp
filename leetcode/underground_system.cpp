// An underground railway system is keeping track of customer travel times between different stations.
// They are using this data to calculate the average time it takes to travel from one station to another.
// A customer with a card ID equal to id, checks in at the station stationName at time t.
// A customer can only be checked into one place at a time.
// A customer with a card ID equal to id, checks out from the station stationName at time t.
// double getAverageTime(string startStation, string endStation)
// Returns the average time it takes to travel from startStation to endStation.
// The average time is computed from all the previous traveling times from startStation to endStation that happened directly, meaning a check in at startStation followed by a check out from endStation.
// The time it takes to travel from startStation to endStation may be different from the time it takes to travel from endStation to startStation.
// There will be at least one customer that has traveled from startStation to endStation before getAverageTime is called.
// You may assume all calls to the checkIn and checkOut methods are consistent. If a customer checks in at time t1 then checks out at time t2, then t1 < t2. All events happen in chronological order.
//
// Passes 57 of 58 Leetcode tests, last test is in contradict with conditions of the task (consistency of checkins/checkouts).

#include <string>
#include <map>

#include <gtest/gtest.h>

struct CheckinInfo {
    std::string stationCheckIn;
    int timeCheckIn;
};

bool operator == (const CheckinInfo& lhs, const CheckinInfo& rhs) {
    return (lhs.stationCheckIn == rhs.stationCheckIn) && (lhs.timeCheckIn == rhs.timeCheckIn);
}

class UndergroundSystem {
private:
    std::map<int, CheckinInfo> m_currTravelling;
    std::map<std::string, std::map<std::string, std::vector<int>>> m_travelTimes;

public:
    UndergroundSystem() = default;

    std::map<int, CheckinInfo> getCurrTravelling() {
        return m_currTravelling;
    }

    void checkIn(int id, const std::string& stationName, int t) {
        assert(m_currTravelling.count(id) == 0);
        m_currTravelling[id] = {stationName, t};
    }

    void checkOut(int id, const std::string& stationName, int t) {
        assert(m_currTravelling.count(id) != 0);
        int currTravelTime = t - m_currTravelling[id].timeCheckIn;
        assert(currTravelTime > 0);
        m_travelTimes[m_currTravelling[id].stationCheckIn][stationName].push_back(currTravelTime);
        m_currTravelling.erase(id);
    }

    double getAverageTime(const std::string& startStation, const std::string& endStation) {
        double sum_time = 0;
        double noOfTrips = 0;
        for (int t : m_travelTimes[startStation][endStation]) {
            sum_time += t;
            noOfTrips += 1;
        }
        return sum_time / noOfTrips;
    }
};

TEST(undergroundSystem, checkout) {
    UndergroundSystem underground;
    underground.checkIn(42, "Sokol", 10);
    underground.checkIn(12, "Aminyevskaya", 11);
    underground.checkOut(42, "Belorusskaya", 12);
    std::map<int, CheckinInfo> currTravel = {{12, {"Aminyevskaya", 11}}};
    ASSERT_EQ(currTravel, underground.getCurrTravelling());

};

TEST(undergroundSystem, getAvgTime) {
    UndergroundSystem underground;
    underground.checkIn(42, "Sokol", 10);
    underground.checkIn(12, "Sokol", 11);
    underground.checkOut(42, "Belorusskaya", 12);
    underground.checkOut(12, "Belorusskaya", 13);
    underground.checkIn(11, "Sokol", 1);
    underground.checkIn(13, "Sokol", 2);
    underground.checkOut(11, "Belorusskaya", 2);
    underground.checkOut(13, "Belorusskaya", 3);
    ASSERT_EQ(1.5, underground.getAverageTime("Sokol", "Belorusskaya"));
};


