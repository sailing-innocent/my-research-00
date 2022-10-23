#include <gtest/gtest.h>
#include <sail/algorithm/select/select_k_max.hpp>

using namespace sail;

TEST(SAIL_TEST_ALGORITHM, SELECT_K_TH_MAX) {
    std::vector<double> arr1 = {0.0, 3.0, 2.0, 1.0, 5.0};
    // double res = select_k_max(arr1, 3, 0);
    double res = select_k_max(arr1, 3, 1);
    EXPECT_DOUBLE_EQ(res, 2.0);
}
