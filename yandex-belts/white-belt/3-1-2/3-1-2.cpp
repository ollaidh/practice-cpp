#include <cstring>
#include <ctype.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    int nElements;
    std::vector<std::string> v;
    std::string element;

    std::cin >> nElements;

    for (int i = 0; i < nElements; i++) {
        std::cin >> element;
        v.push_back(element);
    }

    std::sort(
        v.begin(),
        v.end(),
        [](std::string a, std::string b){
            std::transform(a.begin(), a.end(), a.begin(), [](unsigned char x){ return std::tolower(x); });
            std::transform(b.begin(), b.end(), b.begin(), [](unsigned char y){ return std::tolower(y); });
            return (a < b);
        }
    );

    for (const auto& element : v) {
        std::cout << element << " ";
    }

    return 0;
}