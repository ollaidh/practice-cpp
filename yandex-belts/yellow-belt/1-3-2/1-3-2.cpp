#include <iostream>
#include <istream>
#include <ostream>
#include <vector>


int main()
{
    uint64_t massTotal = 0;
    int nBlocks;
    int density;
    int a;
    int b;
    int c;
    std::cin >> nBlocks >> density;
    for (int i = 0; i < nBlocks; i++) {
        std::cin >> a >> b >> c;
        massTotal += density * a * b * c;
    }

    std::cout << massTotal << "\n";


    return 0;
}