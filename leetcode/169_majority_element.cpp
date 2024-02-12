// Given an array nums of size n, return the majority element.
// The majority element is the element that appears more than ⌊n / 2⌋ times.
// Majority element always exists in the array.
// Solve linear time and in O(1) space

#include <gtest/gtest.h>

class Solution {
public:
    int majorityElement(std::vector<int>& nums) {
        int counter = 0;
        int result = 0;
        for (int num : nums) {
            if (counter == 0) {
                result = num;
            }
            if (num == result) {
                counter += 1;
            } else {
                counter -= 1;
            }
        }
        return result;
    }
};


TEST(majorityElement, ME) {
    Solution solution = Solution();

    std::vector input1 = {3, 2, 3};
    ASSERT_EQ(3, solution.majorityElement(input1));
    std::vector input2 = {2, 2, 1, 1, 1, 2, 2};
    ASSERT_EQ(2, solution.majorityElement(input2));
    std::vector input3 = {3, 3, 3, 3};
    ASSERT_EQ(3, solution.majorityElement(input3));
    std::vector input4 = {51};
    ASSERT_EQ(5, solution.majorityElement(input4));

}