// Function to find the longest common prefix string amongst an array of strings.
// If there is no common prefix, return an empty string ""

#include <gtest/gtest.h>
#include <vector>


class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        std::string result;
        for (int i = 0; i < size(strs[0]); i++) {
            for (const std::string& word : strs) {
                if (size(word) <= i)
                    return result;
                if (word[i] != strs[0][i]) {
                    return result;
                }
            }
            result.push_back(strs[0][i]);
        }

        return result;
    }
};

TEST(Prefix, commonPrefix) {
    Solution solution = Solution();

    std::vector<std::string> input_1 = {"flower", "flow", "flight"};
    ASSERT_EQ("fl", solution.longestCommonPrefix(input_1));
    std::vector<std::string> input_2 = {"dog", "racecar", "car"};
    ASSERT_EQ("", solution.longestCommonPrefix(input_2));
    std::vector<std::string> input_3 = {"racecar", "racecar", "racecar"};
    ASSERT_EQ("racecar", solution.longestCommonPrefix(input_3));
    std::vector<std::string> input_4 = {"ab", "a", "ac"};
    ASSERT_EQ("a", solution.longestCommonPrefix(input_4));
}