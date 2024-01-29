#include <iomanip>
#include <ios>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>


void outputTable(const std::string& inputPath, std::ostream& stream) {
  std::ifstream input(inputPath);
  int nCols = 0;
  int nRows = 0;

  input >> nRows;
  input.ignore(1);
  input >> nCols;


  if (input) {
    std::string currLine;
    std::getline(input, currLine);
    for (int i = 0; i < nRows; i++) {
      std::getline(input, currLine);
      std::stringstream ss(currLine);
      for (int j = 0; j < nCols; j++) {
        std::getline(ss, currLine, ',');
        stream << std::setw(10);
        stream << currLine;
        if (j < nCols - 1) {
          stream << " ";
        }
      }
      if (i < nRows - 1) {
        stream << std::endl;
      }
    }
  }
}


int main() {
  const std::string inputPath = "input.txt";
  // const std::string inputPath = "/Users/maria/Documents/practice-cpp/practice-cpp/yandex-belts/white-belt/4-2-4/input.txt";

  outputTable(inputPath, std::cout);

  return 0;
}