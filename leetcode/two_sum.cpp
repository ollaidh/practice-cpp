// Leetcode 1. Two Sum
// Given an array of integers nums and an integer target,
// return indices of the two numbers such that they add up to target.
// Each input would have exactly one solution, may not use the same element twice.

#include <vector>
#include <map>
#include <gtest/gtest.h>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::vector<int> result(2);
        std::map<int, int> indexNums;
        for (int i = 0; i < nums.size(); i++) {
            if (indexNums.count(target - nums[i]) > 0) {
                return {indexNums[target - nums[i]], i};
            }
            indexNums[nums[i]] = i;
        }
        return {};
    }
};

TEST(two_sum, twoSum) {
    Solution solution;

    std::vector<int> input1 = {2, 7, 11, 15};
    std::vector<int> result1 = solution.twoSum(input1, 9);
    std::vector<int> expected1{0, 1};
    ASSERT_EQ(expected1, result1);

    std::vector<int> input2 = {3, 2, 4};
    std::vector<int> result2 = solution.twoSum(input2, 6);
    std::vector<int> expected2{1, 2};
    ASSERT_EQ(expected2, result2);

    std::vector<int> input3 = {3, 0, 20, 3};
    std::vector<int> result3 = solution.twoSum(input3, 6);
    std::vector<int> expected3{0, 3};
    ASSERT_EQ(expected3, result3);

    std::vector<int> input4 = {3, 2, 4};
    std::vector<int> result4 = solution.twoSum(input4, 10);
    std::vector<int> expected4{};
    ASSERT_EQ(expected4, result4);

    std::vector<int> input5 = {};
    std::vector<int> result5 = solution.twoSum(input5, 10);
    std::vector<int> expected5{};
    ASSERT_EQ(expected5, result5);
}
