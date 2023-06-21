// Given two integer arrays nums1 and nums2, return an array of their intersection.
// Each element in the result must be unique, return the result in any order.

#include <gtest/gtest.h>
#include <vector>
#include <set>

class Solution {
public:
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::vector<int> intersect;
        std::set<int> snums1(nums1.begin(), nums1.end());

        for (int num : nums2) {
            if (snums1.count(num) > 0) {
                snums1.erase(num);
                intersect.push_back(num);
            }
        }
        return intersect;
    };
};

TEST(two_arrays, intersect) {
    Solution solution = Solution();

    std::vector<int> input_left1 = {1, 2, 2, 1};
    std::vector<int> input_right1 = {2, 2};
    std::vector<int> result1 = {2};
    ASSERT_EQ(result1, solution.intersection(input_left1, input_right1));

    std::vector<int> input_left2 = {4, 9, 5};
    std::vector<int> input_right2 = {9, 4, 9, 8, 4};
    std::vector<int> result2 = {9, 4};
    ASSERT_EQ(result2, solution.intersection(input_left2, input_right2));

    std::vector<int> input_left3 = {4, 9, 5};
    std::vector<int> input_right3 = {};
    std::vector<int> result3 = {};
    ASSERT_EQ(result3, solution.intersection(input_left3, input_right3));

    std::vector<int> input_left4 = {};
    std::vector<int> input_right4 = {};
    std::vector<int> result4 = {};
    ASSERT_EQ(result4, solution.intersection(input_left4, input_right4));
}