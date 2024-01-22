
#include <iostream>
#include <string>
#include <algorithm>

int Factorial(int input) {
    int result = 1;
    if (input >= 0) {
        while (input > 0) {
            result *= input;
            input -= 1;
        }
    }
    return result;
}

int main()
{
    int number;
    std::cin >> number;
    std::cout << Factorial(number);
    return 0;
}