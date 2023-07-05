// Given a string s consisting of words and spaces, return the length of the last word in the string.
// A word is a maximal substring consisting of non-space characters only.

#include <gtest/gtest.h>

class Solution {
public:
    int lengthOfLastWord(std::string s) {
        int result = 0;
        bool is_word = false;
        for (int i = size(s) - 1; i >= 0; i--) {
            if (s[i] != ' ') {
                result += 1;
                is_word = true;
            }
            if (is_word && s[i] == ' ') {
                return result;
            }
        }
        return result;
    }
};

TEST(LLW, lengthLastWord) {
    Solution solution = Solution();

    ASSERT_EQ(5, solution.lengthOfLastWord("Hello World"));
    ASSERT_EQ(4, solution.lengthOfLastWord("   fly me   to   the moon  "));
    ASSERT_EQ(6, solution.lengthOfLastWord("luffy is still joyboy"));
    ASSERT_EQ(4, solution.lengthOfLastWord("aaaa"));
}