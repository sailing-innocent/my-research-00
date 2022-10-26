#include <gtest/gtest.h>
#include <sail/algorithm.h>

using namespace sail;

TEST(SAIL_TEST_LIST, CREATE_LIST_NODE) {
    ListNode<int> ln1(1);
    EXPECT_EQ(ln1.content(), 1);
    ListNode<int> ln2(2);
    EXPECT_EQ(ln2.content(), 2);
    ln1.setNext(ln2);
    ln2.setPrev(ln1);
    EXPECT_EQ(ln1.next().content(), 2);
    EXPECT_EQ(ln2.prev().content(), 1);
}

TEST(SAIL_TEST_LIST, CREATE_LIST)
{
    std::vector<ListNode<int>> vec;
    ListNode<int> ln1(1);
    ListNode<int> ln2(2);
    vec.push_back(ln1);
    vec.push_back(ln2);
    LinkList<int> l(vec);
    EXPECT_EQ(l.content()[0].content(), 1);
    EXPECT_EQ(l.content()[1].content(), 2);
    EXPECT_EQ(l.content()[0].next().content(), 2);
    vec[0] = ln2;
    // NOW l is not independent from vec
    EXPECT_EQ(l.content()[0].content(), 1);
}

