#include <gtest/gtest.h>
#include <sail/algorithm/sort/bubble_sort.hpp>

using namespace sail;

TEST(SAIL_TEST_ALGORITHM, BUBBLE_SORT_DOUBLE) {
    std::vector<double> arr1 = {0.0, 1.0, 3.0, 2.0, 1.0};
    bubble_sort_d(arr1);
    EXPECT_EQ(arr1[0], 0.0);
    EXPECT_EQ(arr1[1], 1.0);
    EXPECT_EQ(arr1[2], 1.0);
    EXPECT_EQ(arr1[3], 2.0);
    EXPECT_EQ(arr1[4], 3.0);
}
