#include <gtest/gtest.h>
#include <iostream>
#include <array>

TEST(ArrayOnStack, Basic) {
    int x = 5;
    int y = 10;
    std::array<int, 3> arr = {1, 2, 42};
    int z = 314;

    int* xp = &x;
    int* yp = &y;
    int* arr0p = &arr[0];
    int* zp = &z;

    ASSERT_TRUE(arr0p > zp);
    ASSERT_TRUE(yp > arr0p);
    ASSERT_TRUE(xp > yp);
}
