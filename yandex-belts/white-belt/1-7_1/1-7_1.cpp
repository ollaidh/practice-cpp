
#include <iostream>

int main()
{
    int number1;
    int number2;
    std::cin >> number1 >> number2;

    if (number2 == 0) {
        std::cout << "Impossible";
    }
    else {
        std::cout << number1 / number2;
    }
    return 0;
}