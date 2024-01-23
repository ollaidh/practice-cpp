
#include <iostream>
#include <string>
#include <vector>

void MoveStrings(std::vector<std::string>& source, std::vector<std::string>& destination) {
    for (auto sr : source) {
        destination.push_back(sr);
    }
    source.clear();
}

int main()
{
    return 0;
}