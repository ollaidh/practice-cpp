// Given a string s which consists of lowercase or uppercase letters,
// return the length of the longest palindrome that can be built with those letters.
// Letters are case sensitive, for example, "Aa" is not considered a palindrome here.

#include <gtest/gtest.h>
#include <map>
#include <string>

class Solution {
public:
    int longestPalindrome(std::string s) {
        std::unordered_map<char, int> letters;
        bool seenOdd = false;
        int result = 0;
        for (char letter : s) {
            if (letters.find(letter) == letters.end()) {
                letters[letter] = 0;
            }
            letters[letter] += 1;
        }
        for (auto iter = cbegin(letters); iter != cend(letters); ++iter) {
            if (iter->second % 2 == 0) {
                result += iter->second;
            } else {
                if (!seenOdd) {
                    result += iter->second;
                    seenOdd = true;
                } else {
                    result += (iter->second - 1);
                }
            }
        }
        return result;
    }
};

TEST(TestLongestPalindrome, lP) {
    Solution solution;

    ASSERT_EQ(7, solution.longestPalindrome("abccccdd"));
    ASSERT_EQ(1, solution.longestPalindrome("a"));
    ASSERT_EQ(1, solution.longestPalindrome("abcdef"));
}