
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

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

std::vector<std::string> PalindromFilter(std::vector<std::string> words, int minLength) {
    std::vector<std::string> result;
    for (auto w : words) {
        if (w.length() >= minLength and IsPalindrom(w)) {
            result.push_back(w);
        }
    }
    return result;
}

int main()
{
    std::vector<std::string> wrds{"assa", "agjk", "ada", "aghjhga"};

    auto result = PalindromFilter(wrds, 4);
    for (auto r : result){
        std::cout << r << " ";
    }
    return 0;
}