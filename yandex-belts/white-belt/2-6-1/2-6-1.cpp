#include <iostream>
#include <string>
#include <set>

int main()
{
    std::set<std::string> lines;
    int nOperations;
    std::cin >> nOperations;

    for (int i = 0; i < nOperations; i++) {
        std::string word;
        std::cin >> word;
        lines.insert(word);
    }
    std::cout << lines.size();

    return 0;
}