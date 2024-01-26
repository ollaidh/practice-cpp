#include <algorithm>
#include <iostream>
#include <string>

class ReversibleString {
public:
  ReversibleString() {
    m_string = "";
  }

  ReversibleString(const std::string& str) {
    m_string = str;
  }

  void Reverse() {
    std::reverse(m_string.begin(), m_string.end());
  }

  std::string ToString() const {
    return m_string;
  }

private:
  std::string m_string;

};

int main() {
  ReversibleString s("live");
  s.Reverse();
  std::cout << s.ToString() << std::endl;

  s.Reverse();
  const ReversibleString& s_ref = s;
  std::string tmp = s_ref.ToString();
  std::cout << tmp << std::endl;

  ReversibleString empty;
  std::cout << '"' << empty.ToString() << '"' << std::endl;

  return 0;
}