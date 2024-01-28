#include <iostream>
#include <fstream>
#include <string>


void printFile(const std::string& path) {
  std::ifstream input(path);
  if (input) {
    std::string line;
    while (std::getline(input, line)) {
      std::cout << line << "\n";
    }
  }
}


int main() {
  const std::string inputPath = "/Users/maria/Documents/practice-cpp/practice-cpp/yandex-belts/white-belt/4-2-1/hello.txt";

  printFile(inputPath);
  return 0;
}