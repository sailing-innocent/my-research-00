#include <gtest/gtest.h>
#include <sail/algorithm.h>

using namespace sail;

TEST(SAIL_TEST_NODE, INT_NODE) {
    Node<int> n1(1);
    int& n1_content = n1.content(); // return an alias of n1 content
    EXPECT_EQ(n1_content, 1);
    // Modify n1_content
    n1_content = 2;
    // Change the content inside
    EXPECT_EQ(n1.content(), 2);
}

TEST(SAIL_TEST_NODE, STRUCT_NODE) {
    struct mystruct {
        int num = 1;
        char c = 'a';
        int fallback() { return 2; }
    };
    mystruct mst;
    Node<mystruct> n1(mst);
    mystruct& n1_content = n1.content();
    EXPECT_EQ(n1_content.num, 1);
}