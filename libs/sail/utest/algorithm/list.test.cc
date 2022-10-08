#include <gtest/gtest.h>
#include <sail/algorithm.h>

using namespace sail;

TEST(SAIL_TEST_LIST, CREATE_LIST_NODE) {
    Node<int> n_1(1);
    EXPECT_EQ(n_1.content(), 1);
    Node<char> n_2('b');
    EXPECT_EQ(n_2.content(), 'b');
}