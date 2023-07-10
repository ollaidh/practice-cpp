// Given an array nums containing n distinct numbers in the range [0, n],
// return the only number in the range that is missing from the array.

#include <gtest/gtest.h>
#include <numeric>

class Solution {
public:
    int missingNumber(std::vector<int>& nums) {
        int maximum = nums.size();
        int sum_perfect = maximum * (maximum + 1) / 2;
        int sum_real = std::accumulate(nums.begin(), nums.end(), 0);
        int result = sum_perfect - sum_real;
        return result;
    }
};


TEST(missingNum, missNum) {
    Solution solution = Solution();

    std::vector input1 = {0, 1};
    ASSERT_EQ(2, solution.missingNumber(input1));

    std::vector input2 = {3, 0, 1};
    ASSERT_EQ(2, solution.missingNumber(input2));

    std::vector input3 = {9, 6, 4, 2, 3, 5, 7, 0, 1};
    ASSERT_EQ(8, solution.missingNumber(input3));

}