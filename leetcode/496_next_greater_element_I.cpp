// The next greater element of some element x in an array is the first greater element
// that is to the right of x in the same array.
// Given two distinct 0-indexed integer arrays nums1 and nums2, where nums1 is a subset of nums2.
// For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j] and
// determine the next greater element of nums2[j] in nums2. If there is no next greater element,
// then the answer for this query is -1.
// Return an array ans of length nums1.length such that ans[i] is the next greater element as described above.

#include <gtest/gtest.h>
#include <vector>
#include <map>

class Solution {
public:
    std::vector<int> nextGreaterElement(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::vector<int> result(nums1.size());
        std::vector<int> stack;
        std::unordered_map<int, int> greaters;

        for (size_t j = nums2.size(); j > 0; j--) {
            size_t i = j - 1;
            greaters[nums2[i]] = -1;
            while (!stack.empty() && (stack.back() <  nums2[i])) {
                stack.pop_back();
            }
            if (not stack.empty()) {
                greaters[nums2[i]] = stack.back();
            }
            stack.push_back(nums2[i]);
        }

        for (int i = 0; i < nums1.size(); i++) {
            result[i] = greaters[nums1[i]];
        }

        return result;
    }
};

TEST(TestNGE, nextGreaterElem) {
    Solution solution;

    std::vector<int> expected1 = {-1, 3, -1};
    std::vector<int> input11 = {4, 1, 2};
    std::vector<int> input12 = {1, 3, 4, 2};
    ASSERT_EQ(expected1, solution.nextGreaterElement(input11, input12));

    std::vector<int> expected2 = {3, -1};
    std::vector<int> input21 = {2, 4};
    std::vector<int> input22 = {1, 2, 3, 4};
    ASSERT_EQ(expected1, solution.nextGreaterElement(input11, input12));
}