#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "phone_number.h"

using namespace std;

PhoneNumber::PhoneNumber(const string &international_number) {
  char delim = '-';
  auto endCountry = international_number.find(delim);
  country_code_ = (international_number.substr(0, endCountry)).erase(0, 1);
  auto remaining = international_number.substr(endCountry + 1, international_number.size());
  auto endCity = remaining.find(delim);
  if (endCity == std::string::npos || endCountry == std::string::npos || country_code_ == "") {
    throw invalid_argument("error");
  }
  city_code_ = remaining.substr(0, endCity);
  local_number_ = remaining.substr(endCity + 1, remaining.size());
}

std::string PhoneNumber::GetCountryCode() const {
  return country_code_;
}

std::string PhoneNumber::GetCityCode() const {
  return city_code_;
}

std::string PhoneNumber::GetLocalNumber() const {
  return local_number_;
}

std::string PhoneNumber::GetInternationalNumber() const {
  return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}

#ifdef LOCAL_RUN

int main() {
  PhoneNumber number{"1-2-33"};
  std::cout << "Country: " << number.GetCountryCode() << "\n";
  std::cout << "City: " << number.GetCityCode() << "\n";
  std::cout << "Local: " << number.GetLocalNumber() << "\n";
  std::cout << "All: " << number.GetInternationalNumber() << "\n";

  return 0;
}

#endif