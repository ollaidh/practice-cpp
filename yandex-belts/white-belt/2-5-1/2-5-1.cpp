#include <iostream>
#include <string>
#include <map>

std::map<char, int> countLetters(std::string word) {
    std::map<char, int> result;
    for (char letter : word) {
        result[letter]++;
    }
    return result;
}

bool isAnagrams(std::string word1, std::string word2) {
    auto lettersCounter1 = countLetters(word1);
    auto lettersCounter2 = countLetters(word2);
    return (lettersCounter1 == lettersCounter2);
}



int main()
{
    int nOperations;
    std::cin >> nOperations;
    std::string word1;
    std::string word2;

    for (int i = 0; i < nOperations; i++) {
        std::cin >> word1;
        std::cin >> word2;
        if (isAnagrams(word1, word2)) {
            std::cout << "YES" << "\n";
        } else {
            std::cout << "NO" << "\n";
        }
    }

    return 0;
}