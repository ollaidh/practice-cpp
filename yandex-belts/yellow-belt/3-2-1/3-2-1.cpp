#include <algorithm>
#include <string>
#include <vector>

#include "3-2-1.h"

using namespace std;

int Sum(int x, int y) {
  return x + y;
}

string Reverse(string s) {
    std::reverse(s.begin(), s.end());
    return s;
}

void Sort(vector<int>& nums) {
  std::sort(nums.begin(), nums.end());
}

// int main() {
//   return 0;
// }
