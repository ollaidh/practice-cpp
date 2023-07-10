#include <gtest/gtest.h>

template <typename T>
T square(T x)
{
    static_assert(std::is_arithmetic<T>::value);
    return x * x;
}

char square(char x) = delete;

TEST(squareFunc, sqr) {
    ASSERT_EQ(4, square(2));
    ASSERT_EQ(4.41, square(2.1));
    ASSERT_EQ(1, square(true));
}
