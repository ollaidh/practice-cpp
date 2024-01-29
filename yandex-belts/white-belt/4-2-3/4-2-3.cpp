#include <iomanip>
#include <ios>
#include <iostream>
#include <fstream>
#include <ostream>


void writeToFileWithPrecision(const std::string& inputPath, std::ostream& stream) {
  std::ifstream input(inputPath);


  stream << std::fixed << std::setprecision(3);
  if (input) {
    float line;
    while (input >> line) {
      // input >> line;
      stream << std::fixed << std::setprecision(3);
      stream  << line << std::endl;
    }
  }
}


int main() {
  // const std::string inputPath = "input.txt";
  const std::string inputPath = "/Users/maria/Documents/practice-cpp/practice-cpp/yandex-belts/white-belt/4-2-3/input.txt";

  writeToFileWithPrecision(inputPath, std::cout);

  return 0;
}