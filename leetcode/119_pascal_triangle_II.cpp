// Given an integer rowIndex, return the rowIndexth (0-indexed) row of the Pascal's triangle

#include <gtest/gtest.h>

class Solution {
public:
    std::vector<int> getRow(int rowIndex) {
        if (rowIndex == 0) {
            return {1};
        }
        if (rowIndex == 1) {
            return {1, 1};
        }

        std::vector<int> result(rowIndex + 1, 0);
        result[0] = 1;
        result[1] = 1;

        for (int i = 2; i <= rowIndex; i++){
            int backup = 1;
            for (int j = 1; j < i; j++) {
                int stash = result[j];
                result[j] += backup;
                backup = stash;
            }
            result[i] = 1;
        }
        return result;
    }
};


TEST(PascalTriangleII, PascalTriangII) {
    Solution solution = Solution();

    std::vector<int> result_1 = {1, 3, 3, 1};
    ASSERT_EQ(result_1, solution.getRow(3));
    std::vector<int> result_2 = {1};
    ASSERT_EQ(result_2, solution.getRow(0));
    std::vector<int> result_3 = {1, 1};
    ASSERT_EQ(result_3, solution.getRow(1));
}