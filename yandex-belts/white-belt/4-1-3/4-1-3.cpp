#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Image {
  double quality;
  double freshness;
  double rating;
};

struct Params {
  double a;
  double b;
  double c;
};

class FunctionPart {
public:
  FunctionPart(char operation, double value)
  : m_operation(operation)
  , m_value(value)
  {}

  double Apply(double input) const {
    std::map<char, double> operations = {
      {'+', input + m_value},
      {'-', input - m_value},
      {'*', input * m_value},
      {'/', input / m_value}
    };
    return operations[m_operation];
  }

  void Invert() {
    std::map<char, char> operations = {{'+', '-'}, {'-', '+'}, {'*', '/'}, {'/', '*'}};
    m_operation = operations[m_operation];
  }

private:
  char m_operation;
  double m_value;
};

class Function {
private:
  std::vector<FunctionPart> parts;

public:
  void AddPart(char operation, double part) {
    parts.push_back({operation, part});
  }

  double Apply(double input) const {
    for (auto& part : parts) {
      input = part.Apply(input);
    }
    return input;
  }

  void Invert() {
    for (auto& part : parts) {
      part.Invert();
    }
    std::reverse(parts.begin(), parts.end());
  }
};

Function MakeWeightFunction(const Params& params,
                            const Image& image) {
  Function function;
  function.AddPart('*', params.a);
  function.AddPart('-', image.freshness * params.b);
  function.AddPart('+', image.rating * params.c);
  return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
  Function function = MakeWeightFunction(params, image);
  return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params,
                              const Image& image,
                              double weight) {
  Function function = MakeWeightFunction(params, image);
  function.Invert();
  return function.Apply(weight);
}

int main() {
  Image image = {10, 2, 6};
  Params params = {4, 2, 6};
  std::cout << ComputeImageWeight(params, image) << std::endl;
  std::cout << ComputeQualityByWeight(params, image, 52) << std::endl;
  return 0;
}