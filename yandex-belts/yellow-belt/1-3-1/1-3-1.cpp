
#include <cstddef>
#include <iostream>
#include <istream>
#include <ostream>
#include <vector>

class Temperatures {
    std::vector<int> temperatures;
    int64_t averageTemperature = 0;

public:
    Temperatures() = default;

    Temperatures(std::istream& stream) {
        read(stream);
    }

    void read(std::istream& stream) {
        int nMeasurements;
        stream >> nMeasurements;
        temperatures.clear();
        averageTemperature = 0;
        temperatures.reserve(nMeasurements);
        for (int i = 0; i < nMeasurements; i++) {
            int t;
            stream >> t;
            temperatures.push_back(t);
            averageTemperature += t;
        }
        averageTemperature /= nMeasurements;
    }

    void outputExceedingMeasurements(std::ostream& stream) {
        int counter = 0;
           for (size_t i = 0; i < temperatures.size(); i++) {
            if (temperatures[i] > averageTemperature) {
                counter++;
            }
        }

        stream << counter << "\n";

        for (size_t i = 0; i < temperatures.size(); i++) {
            if (temperatures[i] > averageTemperature) {
                stream << i << " ";
            }
        }
    }

};

int main()
{
    Temperatures t(std::cin);
    t.outputExceedingMeasurements(std::cout);
    return 0;
}