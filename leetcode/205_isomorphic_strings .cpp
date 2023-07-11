#include <gtest/gtest.h>
#include <map>

class Solution {
public:
    bool isIsomorphic(std::string lhs, std::string rhs) {
        std::unordered_map<char, char> relations_lhs;
        std::unordered_map<char, char> relations_rhs;
        for (int i = 0; i < lhs.size(); i ++) {
            if (relations_lhs.find(lhs[i]) == relations_lhs.end()) {
                relations_lhs[lhs[i]] = rhs[i];
            }
            if (relations_rhs.find(rhs[i]) == relations_rhs.end()) {
                relations_rhs[rhs[i]] = lhs[i];
            }
            if ((relations_lhs[lhs[i]] != rhs[i]) || (relations_rhs[rhs[i]] != lhs[i])) {
                return false;
            }
        }
        return true;
    }
};

TEST(isIsomorph, isIsom) {
    Solution solution;
    ASSERT_TRUE(solution.isIsomorphic("foo", "zaa"));
    ASSERT_TRUE(solution.isIsomorphic("qwerty", "asdfgh"));
    ASSERT_TRUE(solution.isIsomorphic("fozo", "zara"));
    ASSERT_FALSE(solution.isIsomorphic("ooops", "spooo"));
    ASSERT_FALSE(solution.isIsomorphic("ywerty", "asdfgh"));
    ASSERT_FALSE(solution.isIsomorphic("badc", "baba"));
    ASSERT_TRUE(solution.isIsomorphic("paper", "title"));
    ASSERT_TRUE(solution.isIsomorphic("q", "q"));
    ASSERT_TRUE(solution.isIsomorphic("q", "c"));
}