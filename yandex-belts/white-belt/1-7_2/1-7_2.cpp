
#include <iostream>
#include <string>
#include <algorithm>

// int main()
// {
//     float price;
//     float cutoff1;
//     float cutoff2;
//     float disc1;
//     float disc2;

//     std::cin >> price >> cutoff1 >> cutoff2 >> disc1 >> disc2;

//     if (price <= cutoff1) {
//         std::cout << price;
//     } else if (price <= cutoff2) {
//         std::cout << price * (100 - disc1) / 100;
//     } else {
//         std::cout << price * (100 - disc2) / 100;
//     }

//     return 0;
// }

// print even numbers in given interval
// int main()
// {
//     int a;
//     int b;
//     std::cin >> a >> b;
//     for (int i = a; i <= b; i++) {
//         if (i % 2 == 0) {
//             std::cout << i << " ";
//         }
//     }

//     return 0;
// }

// find position of second appearence of "f"
// int main()
// {
//     std::string input;
//     int counter = -2;

//     std::cin >> input;

//     for (int i = 0; i < input.size(); i++) {
//         if (input[i] == 'f') {
//             counter += 1;
//             if (counter == 0) {
//                 std::cout << i;
//                 return 0;
//             }
//         }
//     }
//     std::cout << counter;


//     return 0;
// }

// find GCD
// int main()
// {
//     int a;
//     int b;
//     std::cin >> a >> b;
//     while (a != 0 && b != 0) {
//         if (a > b) {
//             a = a % b;
//         }
//         else {
//             b = b % a;
//         }
//     }
//     std::cout << a + b;

//     return 0;
// }

// decimal to binary:
int main()
{
    int decimal;
    std::cin >> decimal;
    std::string binary;

    while (decimal != 0) {
        binary.append(std::to_string(decimal % 2));
        decimal /= 2;
    }

    std::reverse(binary.begin(), binary.end());
    std::cout << binary;

    return 0;
}