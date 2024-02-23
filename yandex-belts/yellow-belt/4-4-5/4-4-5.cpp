#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <deque>



int main() {
    std::string initNumber;
    std::cin >> initNumber;

    int nOps;
    std::cin >> nOps;

    std::string operation;
    std::string currNumber;

    std::deque<std::string> expression{initNumber};

    for (int i = 0; i < nOps; i++) {
        expression.push_front("(");
        expression.push_back(")");

        std::cin >> operation;
        std::cin >> currNumber;

        expression.push_back(" ");
        expression.push_back(operation);
        expression.push_back(" ");

        expression.push_back(currNumber);

    }

    for (const auto& element : expression) {
        std::cout << element;
    }
    std::cout << std::endl;


    return 0;
}