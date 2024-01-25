#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    int nElements;
    std::vector<int> v;
    int element;

    std::cin >> nElements;

    for (int i = 0; i < nElements; i++) {
        std::cin >> element;
        v.push_back(element);
    }

    std::sort(
        v.begin(),
        v.end(),
        [](const int a, const int b){return (abs(a) < abs(b));}
    );

    for (const auto& element : v) {
        std::cout << element << " ";
    }

    return 0;
}