#include <ios>
#include <iostream>
#include <fstream>
#include <string>


void readWrireFile(const std::string& inputPath, const std::string& writePath) {
  std::ifstream input(inputPath);
  std::ofstream output(writePath);

  if (input && output) {
    std::string line;
    while (std::getline(input, line)) {
      output << line << std::endl;
    }
  }
}


int main() {
  const std::string inputPath = "input.txt";
  const std::string outputPath = "output.txt";

  readWrireFile(inputPath, outputPath);
  return 0;
}