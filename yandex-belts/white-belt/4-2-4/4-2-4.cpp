#include <iomanip>
#include <ios>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>


void outputTable(const std::string& inputPath, std::ostream& stream) {
  std::ifstream input(inputPath);
  if (input) {
    std::string currLine;
    std::getline(input, currLine);
    while (std::getline(input, currLine)) {
      std::stringstream ss(currLine);
      while(std::getline(ss, currLine, ',')){
        stream << std::setw(10);
        stream << currLine;
      }
      stream << std::endl;
    }
  }
}


int main() {
  // const std::string inputPath = "input.txt";
  const std::string inputPath = "/Users/maria/Documents/practice-cpp/practice-cpp/yandex-belts/white-belt/4-2-4/input.txt";

  outputTable(inputPath, std::cout);

  return 0;
}