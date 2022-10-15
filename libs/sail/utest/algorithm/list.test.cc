#include <gtest/gtest.h>
#include <sail/algorithm.h>

using namespace sail;

TEST(SAIL_TEST_LIST, CREATE_LIST_NODE) {
    ListNode<int> ln1(1);
    int& ln1_content = ln1.content();
    EXPECT_EQ(ln1_content, 1);
    // ListNode<int> ln2(2);
}
