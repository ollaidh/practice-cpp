
#include <iostream>
#include <string>
#include <vector>

std::vector<int> Reversed(std::vector<int> sequence) {
    int lp = 0;
    int rp = sequence.size() - 1;
    while (lp < rp) {
        std::swap(sequence[lp], sequence[rp]);
        lp += 1;
        rp -= 1;
    }
    return sequence;
}

int main()
{
    return 0;
}