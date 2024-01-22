
#include <iostream>
#include <string>
#include <algorithm>

bool IsPalindrom(std::string input) {
    int lp = 0;
    int rp = input.length() - 1;
    while (lp <= rp) {
        if (input[lp] != input[rp]) {
            return false;
        }
        lp += 1;
        rp -= 1;
    }
    return true;
}

int main()
{
    std::string line;
    std::cin >> line;
    std::cout << IsPalindrom(line);
    return 0;
}