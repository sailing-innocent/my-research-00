/**
 * LEETCODE:001:TwoSums
 * CREATE:2022-10-12
 * DONE: //TODO
*/


#include <gtest/gtest.h>
#include <vector>

using std::vector;

vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> output = {};
    size_t len = nums.size();
    for (auto i = 0; i < len-1; i++) {
        for (auto j = 1; j < len; j++) {
            if (nums[i] + nums[j] == target) {
                output.push_back(i);
                output.push_back(j);
            }
        }
    }
    return output;
}

TEST(SAIL_TEST_LC01, TWO_SUM_SUIT01) {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    vector<int> expected = {0, 1};
    vector<int> output = twoSum(nums, target);
    EXPECT_EQ(expected, output);
}

TEST(SAIL_TEST_LC01, TWO_SUM_SUIT02) {
    vector<int> nums = {3, 2, 4};
    int target = 6;
    vector<int> expected = {1, 2};
    vector<int> output = twoSum(nums, target);
    EXPECT_EQ(expected, output);
}
