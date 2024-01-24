#include <iostream>
#include <string>
#include <set>
#include <map>

int main()
{
    std::map<std::string, std::set<std::string>> thesaurus;
    int nOperations;
    std::string command;

    std::cin >> nOperations;

    for (int i = 0; i < nOperations; i++) {
        std::cin >> command;
        if (command == "ADD") {
            std::string word1;
            std::string word2;
            std::cin >> word1;
            std::cin >> word2;
            thesaurus[word1].insert(word2);
            thesaurus[word2].insert(word1);
        } else if (command == "COUNT") {
            std::string word1;
            std::cin >> word1;
            if (thesaurus.find(word1) == thesaurus.end()) {
                std::cout << "0" << "\n";
            } else {
                std::cout << thesaurus[word1].size() << "\n";
            }
        } else if (command == "CHECK") {
            std::string word1;
            std::string word2;
            std::cin >> word1;
            std::cin >> word2;
            if (thesaurus[word1].count(word2) == 1 || thesaurus[word2].count(word1) == 1) {
                std::cout << "YES" << "\n";
            } else {
                std::cout << "NO" << "\n";
            }
        }
    }

    return 0;
}