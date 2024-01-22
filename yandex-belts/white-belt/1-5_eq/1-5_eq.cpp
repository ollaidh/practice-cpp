#include <cmath>
#include <cstddef>
#include <iostream>
#include <set>
// #include <gtest/gtest.h>

std::set<float> find_roots(float a, float b, float c) {
    std::set<float> roots = {};
    float discr = b * b - 4 * a * c;
    if (discr < 0 || (a == 0 && b == 0)) {
        return roots;
    }

    if (a == 0) {
        float x1 = - c / b;
        roots.insert(x1);
    } else {
        float sqrt_discr = std::sqrt(discr);
        float x1 = (- b + sqrt_discr) / (2 * a);
        float x2 = (- b - sqrt_discr) / (2 * a);
        roots.insert(x1);
        float delta = 0.000000001;
        if (std::abs(x2 - x1) > delta) {
            roots.insert(x2);
        }
    }
    return roots;
}

int main()
{
    float a;
    float b;
    float c;
    std::cin >> a >> b >> c;

    auto roots = find_roots(a, b, c);

    for (auto root : roots) {
        std::cout << root << " ";
    }

}