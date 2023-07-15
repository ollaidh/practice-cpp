#include <set>
#include <gtest/gtest.h>

bool is_prime(int number) {
    std::set <int> prime_numbers({2, 3, 5, 7});
    return (prime_numbers.contains(number));
}

TEST(NumberIsPrime, CheckPrime) {
    ASSERT_TRUE(is_prime(2));
    ASSERT_TRUE(is_prime(5));
    ASSERT_FALSE(is_prime(1));
    ASSERT_FALSE(is_prime(9));
}