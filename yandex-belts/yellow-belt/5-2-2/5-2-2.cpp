#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <memory>

class Figure {

public:
  virtual std::string Name() const = 0;
  virtual double Perimeter() const = 0;
  virtual double Area() const = 0;
};

class Rect : public Figure{
public:
  Rect(const std::string& name, double width, double height)
  : m_name(name)
  , m_perimeter(2 * width + 2 * height)
  , m_area(width * height)
  {}

  std::string Name() const override {
    return m_name;
  }

  double Perimeter() const override {
    return m_perimeter;
  }

  double Area() const override {
    return m_area;
  }

private:
  std::string m_name;
  double m_perimeter;
  double m_area;
};

class Triangle : public Figure{
public:
  Triangle(const std::string& name, double a, double b, double c)
  : m_name(name)
  , m_perimeter(a + b + c)
  , m_area(area(a, b, c))
  {}

  double area(double a, double b, double c) {
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
  }

  std::string Name() const override {
    return m_name;
  }

  double Perimeter() const override {
    return m_perimeter;
  }

  double Area() const override {
    return m_area;
  }

private:
  std::string m_name;
  double m_perimeter;
  double m_area;
};

class Circle : public Figure{
public:
  Circle(const std::string& name, double r)
  : m_name(name)
  , m_perimeter(2 * 3.14 * r)
  , m_area(3.14 * r * r)
  {}

  std::string Name() const override {
    return m_name;
  }

  double Perimeter() const override {
    return m_perimeter;
  }

  double Area() const override {
    return m_area;
  }

private:
  std::string m_name;
  double m_perimeter;
  double m_area;
};

std::pair<std::string, std::vector<double>> getFigureParameters(std::istringstream& commandLine) {
  std::vector<double> parameters;
    std::string word;
    std::string figType;
    commandLine >> figType;
    double param;
    while (commandLine >> param) {
        parameters.push_back(param);
    }
    return {figType, parameters};
}

std::shared_ptr<Figure> CreateFigure(std::istringstream& commandLine) {
    auto [figType, parameters] = getFigureParameters(commandLine);

    auto nParam = parameters.size();
    if(nParam == 1) {
      return std::make_shared<Circle>(figType, parameters[0]);
    } else if (nParam == 2) {
      return std::make_shared<Rect>(figType, parameters[0], parameters[1]);
    }
    return std::make_shared<Triangle>(figType, parameters[0], parameters[1], parameters[2]);
}

int main() {
  std::vector<std::shared_ptr<Figure>> figures;
  for (std::string line; getline(std::cin, line); ) {
    std::istringstream is(line);

    std::string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        std::cout << std::fixed << std::setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << std::endl;
      }
    }
  }
  return 0;
}