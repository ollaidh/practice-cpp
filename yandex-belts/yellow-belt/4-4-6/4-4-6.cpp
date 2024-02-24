#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <deque>

bool opIsGreater(const std::string& lop, const std::string& rop) {
    if ((lop == "/" || lop == "*") && (rop == "-" || rop == "+")) {
        return true;
    }
    return false;
}

int main() {
    std::string initNumber;
    std::cin >> initNumber;

    int nOps;
    std::cin >> nOps;

    std::string currOperation;
    std::string prevOperation;

    std::string currNumber;

    std::deque<std::string> expression{initNumber};

    for (int i = 0; i < nOps; i++) {
        std::cin >> currOperation;
        std::cin >> currNumber;
        if (opIsGreater(currOperation, prevOperation)) {
            expression.push_front("(");
            expression.push_back(")");
        }




        expression.push_back(" ");
        expression.push_back(currOperation);
        expression.push_back(" ");

        expression.push_back(currNumber);

        prevOperation = currOperation;

    }

    for (const auto& element : expression) {
        std::cout << element;
    }
    std::cout << std::endl;


    return 0;
}