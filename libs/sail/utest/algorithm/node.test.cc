#include <gtest/gtest.h>
#include <sail/algorithm.h>

using namespace sail;

TEST(SAIL_TEST_NODE, INT_NODE) {
    Node<int> n1(1);
    const int n1_content = n1.content();
    EXPECT_EQ(n1_content, 1);

    // copy construct
    Node<int> n2(n1);
    EXPECT_EQ(n1.content(), 1);

    // copy operator = 
    Node<int> n3;
    n3 = n1;
    EXPECT_EQ(n3.content(), 1);

    n2.setContent(2);
    EXPECT_EQ(n2.content(), 2);
}

TEST(SAIL_TEST_NODE, STRUCT_NODE) {}