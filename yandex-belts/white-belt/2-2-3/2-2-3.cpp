
#include <iostream>
#include <string>
#include <vector>

void Reverse(std::vector<int>& sequence) {
    int lp = 0;
    int rp = sequence.size() - 1;
    while (lp < rp) {
        std::swap(sequence[lp], sequence[rp]);
        lp += 1;
        rp -= 1;
    }
}

int main()
{
    std::vector<int> seq{1, 2, 3, 4, 5};
    Reverse(seq);
    for (auto s : seq){
        std::cout << s << " ";
    }
    return 0;
}