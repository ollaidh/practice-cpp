// Given an array nums of n integers where nums[i] is in the range [1, n],
// return an array of all the integers in the range [1, n] that do not appear in nums.

#include <gtest/gtest.h>
#include <vector>
#include <unordered_set>

class Solution {
public:
    template<typename T>
    std::vector<T> findDisappearedNumbers(std::vector<T>& nums) {
        std::vector<T> result;
        result.reserve(nums.size());
        std::unordered_set<T> present;

        for (T num : nums) {
            present.insert(num);
        }

        for (int i = 1; i <= nums.size(); i++) {
            if (present.find(i) == present.end())
                result.push_back(i);
        }
        return result;
    }
};

TEST(TestNumDissap, findDisappearedNumbs) {
    Solution solution;

    std::vector<int> input1 = {4, 3, 2, 7, 8, 2, 3, 1};
    std::vector<int> result1 = {5, 6};
    ASSERT_EQ(result1, solution.findDisappearedNumbers(input1));

    std::vector<int> input2 = {1, 1};
    std::vector<int> result2 = {2};
    ASSERT_EQ(result2, solution.findDisappearedNumbers(input2));
}

TEST(TestNumDissap, findDisappearedNumbsLong) {
    Solution solution;

    std::vector<int64_t> input1 = {4, 3, 2, 7, 8, 2, 3, 1};
    std::vector<int64_t> result1 = {5, 6};
    ASSERT_EQ(result1, solution.findDisappearedNumbers<int64_t>(input1));

    std::vector<int64_t> input2 = {1, 1};
    std::vector<int64_t> result2 = {2};
    ASSERT_EQ(result2, solution.findDisappearedNumbers<int64_t>(input2));
}

