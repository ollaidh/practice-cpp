#include <iostream>
#include <string>
#include <map>
#include <vector>

int main()
{
    std::map<std::vector<std::string>, int> routes;
    int routeNumber = 1;

    int nOperations;
    std::cin >> nOperations;

    for (int i = 0; i < nOperations; i++) {
        int stopsNumber;
        std::vector<std::string> currRoute;
        std::cin >> stopsNumber;
        for (int j = 0; j < stopsNumber; j++) {
            std::string stop;
            std::cin >> stop;
            currRoute.push_back(stop);
        }
        if (routes.find(currRoute) == routes.end()) {
            routes[currRoute] = routeNumber;
            std::cout << "New bus " << routeNumber << "\n";
            routeNumber++;
        } else {
            std::cout << "Already exists for " << routes[currRoute] << "\n";
        }

    }

    return 0;
}