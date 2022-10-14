#include <gtest/gtest.h>
#include <sail/algorithm.h>

using namespace sail;

TEST(SAIL_TEST_LIST, CREATE_LIST_NODE) {
    Node<int> n_1(1);
    EXPECT_EQ(n_1.content(), 1);
    Node<char> n_2('b');
    EXPECT_EQ(n_2.content(), 'b');
}

TEST(SAIL_TEST_LIST, INIT_LIST) {
    Node<int> n1(1);
    List<int> lst;
    lst.addNode(n1);
    std::vector<Node<int>> nodes = lst.getNodes();
    EXPECT_EQ(nodes[0].content(), 1);
}