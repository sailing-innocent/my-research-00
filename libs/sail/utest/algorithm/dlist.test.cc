#include <gtest/gtest.h>
#include <sail/algorithm.h>

using namespace sail;

TEST(SAIL_TEST_DLIST, CREATE_LIST_NODE)
{
    DListNode ln1(1.1);
    EXPECT_EQ(ln1.content(), 1.1);
    DListNode ln2(2.0);
    EXPECT_EQ(ln2.content(), 2.0);
    ln1.setNext(ln2);
    ln2.setPrev(ln1);
    EXPECT_EQ(ln1.next().content(), 2.0);
    EXPECT_EQ(ln2.prev().content(), 1.1);
}